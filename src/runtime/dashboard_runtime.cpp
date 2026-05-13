#include "dashboard_runtime.h"

DashboardRuntime::DashboardRuntime(
    QObject* parent
)
    : QObject(parent)
{
    refreshPorts();
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

    emit currentPortChanged();
}

void DashboardRuntime::refreshPorts()
{
    m_availablePorts.clear();

    const auto ports =
        QSerialPortInfo::availablePorts();

    for (const auto& port : ports)
    {
        m_availablePorts.append(
            port.systemLocation()
        );
    }

    //
    // AUTO SELECT FIRST PORT
    //

    if (
        !m_availablePorts.isEmpty()
        && m_currentPort.isEmpty()
    )
    {
        m_currentPort =
            m_availablePorts.first();

        emit currentPortChanged();
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

    emit connectionChanged();

    emit stateChanged();
}

void DashboardRuntime::setFirmwareVersion(
    const QString& version
)
{
    m_firmwareVersion = version;

    emit firmwareChanged();
}