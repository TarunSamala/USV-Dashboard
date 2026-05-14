#pragma once

#include <QObject>

#include <QStringList>

#include <QSerialPortInfo>

#include <QTimer>

class DashboardRuntime : public QObject
{
    Q_OBJECT

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

    Q_PROPERTY(
        QString firmwareVersion
        READ firmwareVersion
        NOTIFY firmwareChanged
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
    // Runtime state
    //

    bool connected() const;

    QString connectionStatus() const;

    //
    // Serial ports
    //

    QStringList availablePorts() const;

    QString currentPort() const;

    void setCurrentPort(
        const QString& port
    );

    Q_INVOKABLE void refreshPorts();

    //
    // Firmware
    //

    QString firmwareVersion() const;

    //
    // Runtime updates
    //

    void setConnected(bool value);

    void setFirmwareVersion(
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
    // Runtime state
    //

    State m_state =
        State::DISCONNECTED;

    //
    // Serial ports
    //

    QStringList m_availablePorts;

    QString m_currentPort;

    //
    // Firmware
    //

    QString m_firmwareVersion =
        "FW: UNKNOWN";

    //
    // Periodic port scanner
    //

    QTimer m_portScanTimer;
};