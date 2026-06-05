#include "telemetry_provider.h"

#include <cmath>

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

    m_roll  = packet.roll;
    m_pitch = packet.pitch;
    m_yaw   = packet.yaw;

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

void TelemetryProvider::calibrateBow()
{
    //
    // Capture the current IMU orientation as the new
    // reference.  After this call, displayRoll/Pitch/Yaw
    // will all return zero until the vessel moves again.
    //

    m_bowRollOffset  = m_roll;
    m_bowPitchOffset = m_pitch;
    m_bowYawOffset   = m_yaw;

    emit telemetryChanged();
}

//
// Wrap angle to the range [-180, +180)
//

static double wrapAngle(double angle)
{
    while (angle >  180.0) angle -= 360.0;
    while (angle < -180.0) angle += 360.0;

    return angle;
}

double TelemetryProvider::displayRoll() const
{
    return wrapAngle(m_roll - m_bowRollOffset);
}

double TelemetryProvider::displayPitch() const
{
    return wrapAngle(m_pitch - m_bowPitchOffset);
}

double TelemetryProvider::displayYaw() const
{
    return wrapAngle(m_yaw - m_bowYawOffset);
}
