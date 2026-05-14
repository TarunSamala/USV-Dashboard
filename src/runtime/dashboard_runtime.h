#pragma once

#include <QObject>

#include <QStringList>

#include <QSerialPortInfo>

#include <QTimer>

class DashboardRuntime : public QObject
{
    Q_OBJECT

    //
    // CONNECTION
    //

    Q_PROPERTY(
        bool connected
        READ connected
        NOTIFY connectionChanged
    )

    Q_PROPERTY(
        QString connectionStatus
        READ connectionStatus
        NOTIFY stateChanged
    )

    //
    // SERIAL
    //

    Q_PROPERTY(
        QStringList availablePorts
        READ availablePorts
        NOTIFY portsChanged
    )

    Q_PROPERTY(
        QString currentPort
        READ currentPort
        WRITE setCurrentPort
        NOTIFY currentPortChanged
    )

    //
    // FIRMWARE
    //

    Q_PROPERTY(
        QString firmwareVersion
        READ firmwareVersion
        NOTIFY firmwareChanged
    )

    //
    // DASHBOARD STATE
    //

    Q_PROPERTY(
        QString dashboardState
        READ dashboardState
        NOTIFY dashboardStateChanged
    )

    //
    // ACTIVE TASK
    //

    Q_PROPERTY(
        QString activeTask
        READ activeTask
        NOTIFY activeTaskChanged
    )

    Q_PROPERTY(
        QString taskInstruction
        READ taskInstruction
        NOTIFY taskInstructionChanged
    )

    Q_PROPERTY(
        int taskProgress
        READ taskProgress
        NOTIFY taskProgressChanged
    )

public:

    explicit DashboardRuntime(
        QObject* parent = nullptr
    );

    enum class State
    {
        DISCONNECTED,
        CONNECTING,
        RUNNING,
        ERROR
    };

    //
    // CONNECTION
    //

    bool connected() const;

    QString connectionStatus() const;

    //
    // SERIAL
    //

    QStringList availablePorts() const;

    QString currentPort() const;

    void setCurrentPort(
        const QString& port
    );

    Q_INVOKABLE void refreshPorts();

    //
    // FIRMWARE
    //

    QString firmwareVersion() const;

    //
    // DASHBOARD STATE
    //

    QString dashboardState() const;

    void setDashboardState(
        const QString& state
    );

    //
    // ACTIVE TASK
    //

    QString activeTask() const;

    QString taskInstruction() const;

    int taskProgress() const;

    void setActiveTask(
        const QString& task
    );

    void setTaskInstruction(
        const QString& instruction
    );

    void setTaskProgress(
        int progress
    );

    //
    // RUNTIME UPDATES
    //

    void setConnected(
        bool value
    );

    void setFirmwareVersion(
        const QString& version
    );

signals:

    void connectionChanged();

    void stateChanged();

    void portsChanged();

    void currentPortChanged();

    void firmwareChanged();

    void dashboardStateChanged();

    void activeTaskChanged();

    void taskInstructionChanged();

    void taskProgressChanged();

private:

    //
    // CONNECTION STATE
    //

    State m_state =
        State::DISCONNECTED;

    //
    // SERIAL
    //

    QStringList m_availablePorts;

    QString m_currentPort;

    //
    // DASHBOARD
    //

    QString m_dashboardState =
        "DISCONNECTED";

    //
    // TASK
    //

    QString m_activeTask =
        "IDLE";

    QString m_taskInstruction =
        "Waiting for operation";

    int m_taskProgress = 0;

    //
    // FIRMWARE
    //

    QString m_firmwareVersion =
        "FW: UNKNOWN";

    //
    // PORT SCANNER
    //

    QTimer m_portScanTimer;
};