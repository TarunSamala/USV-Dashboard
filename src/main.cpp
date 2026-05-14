#include <QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

#include "models/telemetry_provider.h"
#include "models/telemetry_parser.h"
#include "models/telemetry_packet.h"

#include "visualization/VesselItem.h"

#include "logger/event_logger.h"
#include "logger/csv_logger.h"

#include "runtime/dashboard_runtime.h"

#include "serial/serial_reader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //
    // REGISTER QML TYPES
    //

    qmlRegisterType<VesselItem>(
        "Dashboard.Visualization",
        1,
        0,
        "VesselView"
    );

    //
    // BACKEND OBJECTS
    //

    TelemetryProvider telemetry;

    EventLogger logger;

    CsvLogger csvLogger;

    SerialReader serialReader;

    DashboardRuntime runtime;

    //
    // SERIAL TELEMETRY PIPELINE
    //

    QObject::connect(
        &serialReader,
        &SerialReader::lineReceived,
        [&](const QString& line)
        {
            //
            // LOG RAW TELEMETRY
            //

            logger.addLog(line);

            //
            // DEBUG OUTPUT
            //

            qDebug() << "LINE:" << line;

            //
            // PARSE TELEMETRY
            //

            TelemetryPacket packet;

            if (
                TelemetryParser::parse(
                    line,
                    packet
                )
            )
            {
                //
                // UPDATE TELEMETRY PROVIDER
                //

                telemetry.updateFromPacket(
                    packet
                );

                //
                // LOG CSV PACKET
                //

                csvLogger.logPacket(
                    packet
                );
            }

            //
            // FIRMWARE ACK
            //

            if (
                line.startsWith("ACK:")
            )
            {
                runtime.setFirmwareVersion(
                    line.mid(4)
                );
            }
        }
    );

    //
    // SERIAL CONNECTED
    //

    QObject::connect(
        &serialReader,
        &SerialReader::serialConnected,
        [&]()
        {
            runtime.setConnected(true);

            logger.addLog(
                "ESP32 serial connected"
            );
        }
    );

    //
    // SERIAL DISCONNECTED
    //

    QObject::connect(
        &serialReader,
        &SerialReader::serialDisconnected,
        [&]()
        {
            runtime.setConnected(false);

            logger.addLog(
                "ESP32 serial disconnected"
            );
        }
    );

    //
    // SERIAL ERROR
    //

    QObject::connect(
        &serialReader,
        &SerialReader::serialError,
        [&](const QString& error)
        {
            runtime.setConnected(false);

            logger.addLog(
                "SERIAL ERROR: " + error
            );

            qWarning() << error;
        }
    );

    //
    // QML ENGINE
    //

    QQmlApplicationEngine engine;

    //
    // CONTEXT PROPERTIES
    //

    engine.rootContext()->setContextProperty(
        "telemetry",
        &telemetry
    );

    engine.rootContext()->setContextProperty(
        "logger",
        &logger
    );

    engine.rootContext()->setContextProperty(
        "runtime",
        &runtime
    );

    engine.rootContext()->setContextProperty(
        "serialReader",
        &serialReader
    );

    engine.rootContext()->setContextProperty(
        "csvLogger",
        &csvLogger
    );

    //
    // INITIAL LOGS
    //

    logger.addLog(
        "Dashboard initialized"
    );

    logger.addLog(
        "Telemetry provider started"
    );

    logger.addLog(
        "Waiting for ESP32 telemetry stream"
    );

    //
    // LOAD DASHBOARD
    //

    engine.loadFromModule(
        "Dashboard",
        "Main"
    );

    if (engine.rootObjects().isEmpty())
        return -1;

    //
    // CLEAN EXIT
    //

    QObject::connect(
        &app,
        &QApplication::aboutToQuit,
        [&]()
        {
            csvLogger.stopLogging();

            serialReader.stop();

            logger.addLog(
                "Dashboard shutdown"
            );
        }
    );

    //
    // START APPLICATION
    //

    return app.exec();
}