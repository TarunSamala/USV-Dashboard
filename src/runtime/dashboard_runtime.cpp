#include "dashboard_runtime.h"

#include <QDebug>

DashboardRuntime::DashboardRuntime(
    QObject* parent
)
    : QObject(parent)
{
    //
    // Initial scan
    //

    refreshPorts();

    //
    // Periodic USB scan
    //

    connect(
        &m_portScanTimer,
        &QTimer::timeout,
        this,
        &DashboardRuntime::refreshPorts
    );

    m_portScanTimer.start(1000);
}

bool DashboardRuntime::connected() const
{
    return m_state == State::RUNNING;
}

QString DashboardRuntime::connectionStatus() const
{
    switch (m_state)
    {
        case State::DISCONNECTED:
            return "DISCONNECTED";

        case State::CONNECTING:
            return "CONNECTING";

        case State::RUNNING:
            return "RUNNING";

        case State::ERROR:
            return "ERROR";
    }

    return "UNKNOWN";
}

QStringList DashboardRuntime::availablePorts() const
{
    return m_availablePorts;
}

QString DashboardRuntime::currentPort() const
{
    return m_currentPort;
}

QString DashboardRuntime::firmwareVersion() const
{
    return m_firmwareVersion;
}

void DashboardRuntime::setCurrentPort(
    const QString& port
)
{
    if (m_currentPort == port)
        return;

    m_currentPort = port;

    qDebug()
        << "Selected port:"
        << m_currentPort;

    emit currentPortChanged();
}

void DashboardRuntime::refreshPorts()
{
    //
    // Clear old list
    //

    m_availablePorts.clear();

    //
    // Scan serial ports
    //

    const auto ports =
        QSerialPortInfo::availablePorts();

    for (const auto& port : ports)
    {
        const QString location =
            port.systemLocation();

        //
        // Linux USB serial
        //

        const bool validLinuxPort =

            location.contains("ttyACM")
            ||

            location.contains("ttyUSB");

#ifdef Q_OS_WIN

        //
        // Windows COM ports
        //

        const bool validWindowsPort =
            location.startsWith("COM");

#else

        const bool validWindowsPort =
            false;

#endif

        //
        // Add valid ports only
        //

        if (
            validLinuxPort
            || validWindowsPort
        )
        {
            if (
                !m_availablePorts.contains(
                    location
                )
            )
            {
                qDebug()
                    << "Detected serial:"
                    << location;

                m_availablePorts.append(
                    location
                );
            }
        }
    }

    //
    // Auto-select valid port
    //

    if (!m_availablePorts.isEmpty())
    {
        if (
            m_currentPort.isEmpty()
            || !m_availablePorts.contains(
                   m_currentPort
               )
        )
        {
            m_currentPort =
                m_availablePorts.first();

            qDebug()
                << "Auto-selected:"
                << m_currentPort;

            emit currentPortChanged();
        }
    }
    else
    {
        //
        // No ports found
        //

        if (!m_currentPort.isEmpty())
        {
            qDebug()
                << "Serial disconnected";

            m_currentPort.clear();

            emit currentPortChanged();
        }
    }

    emit portsChanged();
}

void DashboardRuntime::setConnected(
    bool value
)
{
    m_state = value
        ? State::RUNNING
        : State::DISCONNECTED;

    qDebug()
        << "Runtime connected:"
        << value;

    emit connectionChanged();

    emit stateChanged();
}

void DashboardRuntime::setFirmwareVersion(
    const QString& version
)
{
    m_firmwareVersion = version;

    qDebug()
        << "Firmware version:"
        << version;

    emit firmwareChanged();
}