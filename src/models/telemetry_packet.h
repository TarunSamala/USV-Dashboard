#pragma once

struct TelemetryPacket
{
    double roll = 0.0;
    double pitch = 0.0;
    double yaw = 0.0;
    double heading = 0.0;

    double accelX = 0.0;
    double accelY = 0.0;
    double accelZ = 0.0;

    double gyroX = 0.0;
    double gyroY = 0.0;
    double gyroZ = 0.0;

    double magX = 0.0;
    double magY = 0.0;
    double magZ = 0.0;

    double temperature = 0.0;
};