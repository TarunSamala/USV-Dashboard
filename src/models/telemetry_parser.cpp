#include "telemetry_parser.h"

#include <QStringList>

bool TelemetryParser::parse(
    const QString& line,
    TelemetryPacket& packet
)
{
    if (!line.startsWith("$DATA"))
        return false;

    QStringList parts =
        line.split(',');

    for (const QString& part : parts)
    {
        if (part.startsWith("R:"))
            packet.roll =
                part.mid(2).toDouble();

        else if (part.startsWith("P:"))
            packet.pitch =
                part.mid(2).toDouble();

        else if (part.startsWith("Y:"))
            packet.yaw =
                part.mid(2).toDouble();

        else if (part.startsWith("H:"))
            packet.heading =
                part.mid(2).toDouble();

        else if (part.startsWith("AX:"))
            packet.accelX =
                part.mid(3).toDouble();

        else if (part.startsWith("AY:"))
            packet.accelY =
                part.mid(3).toDouble();

        else if (part.startsWith("AZ:"))
            packet.accelZ =
                part.mid(3).toDouble();

        else if (part.startsWith("GX:"))
            packet.gyroX =
                part.mid(3).toDouble();

        else if (part.startsWith("GY:"))
            packet.gyroY =
                part.mid(3).toDouble();

        else if (part.startsWith("GZ:"))
            packet.gyroZ =
                part.mid(3).toDouble();

        else if (part.startsWith("MX:"))
            packet.magX =
                part.mid(3).toDouble();

        else if (part.startsWith("MY:"))
            packet.magY =
                part.mid(3).toDouble();

        else if (part.startsWith("MZ:"))
            packet.magZ =
                part.mid(3).toDouble();

        else if (part.startsWith("T:"))
            packet.temperature =
                part.mid(2).toDouble();
    }

    return true;
}