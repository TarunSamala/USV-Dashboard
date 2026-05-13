#include "telemetry_provider.h"

#include <cstdlib>

TelemetryProvider::TelemetryProvider(QObject* parent)
    : QObject(parent)
{
    connect(
        &m_timer,
        &QTimer::timeout,
        this,
        &TelemetryProvider::updateTelemetry
    );

    m_timer.start(100);
}

void TelemetryProvider::updateTelemetry()
{
    // ORIENTATION

    m_roll = (std::rand() % 400 - 200) / 10.0;

    m_pitch = (std::rand() % 400 - 200) / 10.0;

    m_yaw += 2.0;

    if (m_yaw > 360.0)
        m_yaw = 0.0;

    // ACCELEROMETER

    m_accelX = (std::rand() % 200 - 100) / 10.0;

    m_accelY = (std::rand() % 200 - 100) / 10.0;

    m_accelZ = 9.0 + (std::rand() % 20) / 10.0;

    // GYROSCOPE

    m_gyroX = (std::rand() % 100 - 50) / 10.0;

    m_gyroY = (std::rand() % 100 - 50) / 10.0;

    m_gyroZ = (std::rand() % 100 - 50) / 10.0;

    // MAGNETOMETER

    m_magX = (std::rand() % 100 - 50);

    m_magY = (std::rand() % 100 - 50);

    m_magZ = (std::rand() % 100 - 50);

    emit telemetryChanged();
}