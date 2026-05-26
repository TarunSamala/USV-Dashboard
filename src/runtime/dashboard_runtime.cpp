
#include "dashboard_runtime.h"

#include <QDebug>

DashboardRuntime::DashboardRuntime(
    QObject* parent
)
    : QObject(parent)
{
    //
    // INITIAL SCAN
    //

    refreshPorts();

    //
    // PERIODIC PORT SCAN
    //

    connect(
        &m_portScanTimer,
        &QTimer::timeout,
        this,
        &DashboardRuntime::refreshPorts
    );

    //
    // SLOWER SCAN
    // REDUCES USB INSTABILITY
    //

    m_portScanTimer.start(2500);
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

QString DashboardRuntime::dashboardState() const
{
    return m_dashboardState;
}

QString DashboardRuntime::activeTask() const
{
    return m_activeTask;
}

QString DashboardRuntime::taskInstruction() const
{
    return m_taskInstruction;
}

int DashboardRuntime::taskProgress() const
{
    return m_taskProgress;
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
    // VERY IMPORTANT
    // DO NOT RESCAN
    // WHILE CONNECTED
    //

    if (connected())
    {
        return;
    }

    QStringList detectedPorts;

    const auto ports =
        QSerialPortInfo::availablePorts();

    for (const auto& port : ports)
    {
#ifdef Q_OS_WIN

        //
        // WINDOWS
        //

        const QString portName =
            port.portName();

        if (
            portName.startsWith("COM")
        )
        {
            if (
                !detectedPorts.contains(
                    portName
                )
            )
            {
                qDebug()
                    << "Detected serial:"
                    << portName;

                detectedPorts.append(
                    portName
                );
            }
        }

#else

        //
        // LINUX
        //

        const QString location =
            port.systemLocation();

        if (
            location.contains("ttyACM")
            ||
            location.contains("ttyUSB")
        )
        {
            if (
                !detectedPorts.contains(
                    location
                )
            )
            {
                qDebug()
                    << "Detected serial:"
                    << location;

                detectedPorts.append(
                    location
                );
            }
        }

#endif
    }

    //
    // UPDATE ONLY IF CHANGED
    //

    if (m_availablePorts != detectedPorts)
    {
        m_availablePorts =
            detectedPorts;

        emit portsChanged();
    }

    //
    // AUTO SELECT
    //

    if (!m_availablePorts.isEmpty())
    {
        if (
            m_currentPort.isEmpty()
            ||
            !m_availablePorts.contains(
                m_currentPort
            )
        )
        {
            m_currentPort =
                m_availablePorts.first();

            emit currentPortChanged();
        }
    }
    else
    {
        if (!m_currentPort.isEmpty())
        {
            m_currentPort.clear();

            emit currentPortChanged();
        }
    }
}

void DashboardRuntime::setConnected(
    bool value
)
{
    m_state = value
        ? State::RUNNING
        : State::DISCONNECTED;

    //
    // DASHBOARD STATE
    //

    m_dashboardState =
        value
        ? "RUNNING"
        : "DISCONNECTED";

    qDebug()
        << "Runtime connected:"
        << value;

    emit connectionChanged();

    emit stateChanged();

    emit dashboardStateChanged();
}

void DashboardRuntime::setFirmwareVersion(
    const QString& version
)
{
    if (m_firmwareVersion == version)
        return;

    m_firmwareVersion = version;

    emit firmwareChanged();
}

void DashboardRuntime::setDashboardState(
    const QString& state
)
{
    if (m_dashboardState == state)
        return;

    m_dashboardState = state;

    emit dashboardStateChanged();
}

void DashboardRuntime::setActiveTask(
    const QString& task
)
{
    if (m_activeTask == task)
        return;

    m_activeTask = task;

    emit activeTaskChanged();
}

void DashboardRuntime::setTaskInstruction(
    const QString& instruction
)
{
    if (m_taskInstruction == instruction)
        return;

    m_taskInstruction = instruction;

    emit taskInstructionChanged();
}

void DashboardRuntime::setTaskProgress(
    int progress
)
{
    if (m_taskProgress == progress)
        return;

    m_taskProgress = progress;

    emit taskProgressChanged();
}
