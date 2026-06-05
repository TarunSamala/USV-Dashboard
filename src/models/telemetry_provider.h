#pragma once

#include <QObject>

#include "telemetry_packet.h"

class TelemetryProvider : public QObject
{
    Q_OBJECT

    //
    // RAW ORIENTATION (from IMU)
    //

    Q_PROPERTY(double roll  READ roll  NOTIFY telemetryChanged)
    Q_PROPERTY(double pitch READ pitch NOTIFY telemetryChanged)
    Q_PROPERTY(double yaw   READ yaw   NOTIFY telemetryChanged)

    //
    // DISPLAY ORIENTATION (calibration-offset applied)
    // These are what the 3D visualizer should use.
    //

    Q_PROPERTY(double displayRoll  READ displayRoll  NOTIFY telemetryChanged)
    Q_PROPERTY(double displayPitch READ displayPitch NOTIFY telemetryChanged)
    Q_PROPERTY(double displayYaw   READ displayYaw   NOTIFY telemetryChanged)

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

    explicit TelemetryProvider(
        QObject* parent = nullptr
    );

    //
    // REAL TELEMETRY UPDATE
    //

    void updateFromPacket(
        const TelemetryPacket& packet
    );

    //
    // BOW CALIBRATION
    //
    // Records the current IMU roll/pitch/yaw as the
    // reference orientation.  All subsequent display
    // values will be relative to this baseline.
    // Call this when the user presses CAL BOW.
    //

    Q_INVOKABLE void calibrateBow();

    //
    // RAW READERS
    //

    double roll()  const { return m_roll;  }
    double pitch() const { return m_pitch; }
    double yaw()   const { return m_yaw;   }

    //
    // DISPLAY READERS (offset-corrected)
    //

    double displayRoll()  const;
    double displayPitch() const;
    double displayYaw()   const;

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

    //
    // ORIENTATION (raw from IMU)
    //

    double m_roll  = 0.0;
    double m_pitch = 0.0;
    double m_yaw   = 0.0;

    //
    // BOW CALIBRATION OFFSETS
    //
    // Captured at the moment CAL BOW is pressed.
    // Display = raw - offset  (yaw wrapped to ±180)
    //

    double m_bowRollOffset  = 0.0;
    double m_bowPitchOffset = 0.0;
    double m_bowYawOffset   = 0.0;

    //
    // ACCELEROMETER
    //

    double m_accelX = 0.0;
    double m_accelY = 0.0;
    double m_accelZ = 0.0;

    //
    // GYROSCOPE
    //

    double m_gyroX = 0.0;
    double m_gyroY = 0.0;
    double m_gyroZ = 0.0;

    //
    // MAGNETOMETER
    //

    double m_magX = 0.0;
    double m_magY = 0.0;
    double m_magZ = 0.0;
};
