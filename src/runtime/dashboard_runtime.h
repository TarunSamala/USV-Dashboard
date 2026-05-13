#pragma once

#include <QObject>

#include <QStringList>

#include <QSerialPortInfo>

class DashboardRuntime : public QObject
{
    Q_OBJECT

    //
    // CONNECTION STATE
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
    // SERIAL PORTS
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
    // FIRMWARE INFO
    //

    Q_PROPERTY(
        QString firmwareVersion
        READ firmwareVersion
        NOTIFY firmwareChanged
    )

public:

    explicit DashboardRuntime(
        QObject* parent = nullptr
    );

    //
    // DASHBOARD STATES
    //

    enum class State
    {
        DISCONNECTED,
        CONNECTING,
        RUNNING,
        ERROR
    };

    Q_ENUM(State)

    //
    // READERS
    //

    bool connected() const;

    QString connectionStatus() const;

    QStringList availablePorts() const;

    QString currentPort() const;

    QString firmwareVersion() const;

    //
    // WRITERS
    //

    void setCurrentPort(
        const QString& port
    );

    //
    // ACTIONS
    //

    Q_INVOKABLE void refreshPorts();

    Q_INVOKABLE void setConnected(
        bool value
    );

    Q_INVOKABLE void setFirmwareVersion(
        const QString& version
    );

signals:

    void connectionChanged();

    void stateChanged();

    void portsChanged();

    void currentPortChanged();

    void firmwareChanged();

private:

    //
    // RUNTIME STATE
    //

    State m_state =
        State::DISCONNECTED;

    //
    // SERIAL
    //

    QStringList m_availablePorts;

    QString m_currentPort;

    //
    // FIRMWARE
    //

    QString m_firmwareVersion =
        "UNKNOWN";
};