#pragma once

#include <QObject>
#include <QTimer>

class TelemetryProvider : public QObject {

    Q_OBJECT

    Q_PROPERTY(double roll READ roll NOTIFY telemetryChanged)
    Q_PROPERTY(double pitch READ pitch NOTIFY telemetryChanged)
    Q_PROPERTY(double yaw READ yaw NOTIFY telemetryChanged)

    Q_PROPERTY(double accelX READ accelX NOTIFY telemetryChanged)
    Q_PROPERTY(double accelY READ accelY NOTIFY telemetryChanged)
    Q_PROPERTY(double accelZ READ accelZ NOTIFY telemetryChanged)

    Q_PROPERTY(double gyroX READ gyroX NOTIFY telemetryChanged)
    Q_PROPERTY(double gyroY READ gyroY NOTIFY telemetryChanged)
    Q_PROPERTY(double gyroZ READ gyroZ NOTIFY telemetryChanged)

    Q_PROPERTY(double magX READ magX NOTIFY telemetryChanged)
    Q_PROPERTY(double magY READ magY NOTIFY telemetryChanged)
    Q_PROPERTY(double magZ READ magZ NOTIFY telemetryChanged)

public:

    explicit TelemetryProvider(QObject* parent = nullptr);

    double roll() const { return m_roll; }
    double pitch() const { return m_pitch; }
    double yaw() const { return m_yaw; }

    double accelX() const { return m_accelX; }
    double accelY() const { return m_accelY; }
    double accelZ() const { return m_accelZ; }

    double gyroX() const { return m_gyroX; }
    double gyroY() const { return m_gyroY; }
    double gyroZ() const { return m_gyroZ; }

    double magX() const { return m_magX; }
    double magY() const { return m_magY; }
    double magZ() const { return m_magZ; }

signals:

    void telemetryChanged();

private:

    QTimer m_timer;

    double m_roll = 0.0;
    double m_pitch = 0.0;
    double m_yaw = 0.0;

    double m_accelX = 0.0;
    double m_accelY = 0.0;
    double m_accelZ = 9.81;

    double m_gyroX = 0.0;
    double m_gyroY = 0.0;
    double m_gyroZ = 0.0;

    double m_magX = 0.0;
    double m_magY = 0.0;
    double m_magZ = 0.0;

    void updateTelemetry();
};