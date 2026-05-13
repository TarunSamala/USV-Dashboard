#include "telemetry_provider.h"

TelemetryProvider::TelemetryProvider(
    QObject* parent
)
    : QObject(parent)
{
}

void TelemetryProvider::updateFromPacket(
    const TelemetryPacket& packet
)
{
    //
    // ORIENTATION
    //

    m_roll = packet.roll;

    m_pitch = packet.pitch;

    m_yaw = packet.yaw;

    //
    // ACCELEROMETER
    //

    m_accelX = packet.accelX;

    m_accelY = packet.accelY;

    m_accelZ = packet.accelZ;

    //
    // GYROSCOPE
    //

    m_gyroX = packet.gyroX;

    m_gyroY = packet.gyroY;

    m_gyroZ = packet.gyroZ;

    //
    // MAGNETOMETER
    //

    m_magX = packet.magX;

    m_magY = packet.magY;

    m_magZ = packet.magZ;

    //
    // NOTIFY QML
    //

    emit telemetryChanged();
}