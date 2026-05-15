#include <QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

#include "models/telemetry_provider.h"
#include "models/telemetry_parser.h"
#include "models/telemetry_packet.h"
#include "logger/system_logger.h"
#include "runtime/calibration_controller.h"

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

    SystemLogger systemLogger;

    CalibrationController calibrationController;
    //
    // SERIAL TELEMETRY PIPELINE
    //

    QObject::connect(
    &serialReader,
    &SerialReader::lineReceived,
    [&](const QString& line)
    {
        //
        // LOGGING
        //
        calibrationController.processLine(
            line
        );
        
        if (line.startsWith("$DATA"))
        {
            logger.addLog(line);
        }
        else
        {
            systemLogger.addLog(line);
        }

        //
        // DEBUG
        //

        qDebug() << "LINE:" << line;
        calibrationController.processLine(
            line
        );
        //
        // TELEMETRY PARSE
        //

        TelemetryPacket packet;

        if (
            TelemetryParser::parse(
                line,
                packet
            )
        )
        {
            telemetry.updateFromPacket(
                packet
            );

            csvLogger.logPacket(
                packet
            );
        }

        //
        // FIRMWARE ACK
        //

        if (line.startsWith("ACK:"))
        {
            runtime.setFirmwareVersion(
                line.mid(4)
            );
        }

        //
        // GYRO CALIBRATION
        //

        if (line.startsWith("CAL:GYRO:START"))
        {
            runtime.setActiveTask(
                "CALIBRATING GYRO"
            );

            runtime.setTaskInstruction(
                "Keep module flat and still"
            );

            runtime.setTaskProgress(0);
        }

        //
        // GYRO PROGRESS
        //

        if (line.startsWith("CAL:GYRO:PROG:"))
        {
            const int progress =
                line.section(':', 3, 3)
                .toInt();

            runtime.setTaskProgress(
                progress
            );
        }

        //
        // GYRO DONE
        //

        if (line.startsWith("CAL:GYRO:DONE"))
        {
            runtime.setTaskProgress(100);

            runtime.setTaskInstruction(
                "Gyro calibration completed"
            );

            runtime.setActiveTask(
                "IDLE"
            );
        }

        //
        // MAG START
        //

        if (line.startsWith("CAL:MAG:START"))
        {
            runtime.setActiveTask(
                "CALIBRATING MAG"
            );

            runtime.setTaskInstruction(
                "Rotate module slowly in all directions"
            );

            runtime.setTaskProgress(0);
        }

        //
        // MAG PROGRESS
        //

        if (line.startsWith("CAL:MAG:PROG:"))
        {
            const QString pct =
                line.section(':', 3, 3)
                .section(',', 0, 0);

            runtime.setTaskProgress(
                pct.toInt()
            );
        }

        //
        // MAG DONE
        //

        if (line.startsWith("CAL:MAG:DONE"))
        {
            runtime.setTaskProgress(100);

            runtime.setTaskInstruction(
                "Magnetometer calibration completed"
            );

            runtime.setActiveTask(
                "IDLE"
            );
        }

        //
        // BOW SETUP
        //

        if (line.startsWith("BOW:START"))
        {
            runtime.setActiveTask(
                "SETTING BOW"
            );

            runtime.setTaskInstruction(
                "Point module toward vessel bow"
            );

            runtime.setTaskProgress(0);
        }

        //
        // BOW COMPLETE
        //

        if (line.startsWith("BOW:OK"))
        {
            runtime.setTaskProgress(100);

            runtime.setTaskInstruction(
                "Bow offset saved"
            );

            runtime.setActiveTask(
                "IDLE"
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

    engine.rootContext()->setContextProperty(
        "systemLogger",
        &systemLogger
    );

    engine.rootContext()->setContextProperty(
        "calibrationController",
        &calibrationController
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