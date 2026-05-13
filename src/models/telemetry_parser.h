#pragma once

#include <QString>

#include "models/telemetry_packet.h"

class TelemetryParser
{
public:

    static bool parse(
        const QString& line,
        TelemetryPacket& packet
    );
};