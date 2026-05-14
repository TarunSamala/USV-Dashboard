#include <QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QWidget>
#include <QVBoxLayout>

#include <QDebug>
#include <QTimer>

#include "widgets/Vessel3DWidget.h"

#include "models/telemetry_provider.h"
#include "models/telemetry_parser.h"
#include "models/telemetry_packet.h"

#include "runtime/dashboard_runtime.h"

#include "logger/event_logger.h"

#include "serial/serial_reader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //
    // BACKEND OBJECTS
    //

    TelemetryProvider telemetry;

    EventLogger logger;

    SerialReader serialReader;

    DashboardRuntime runtime;

    //
    // OPENGL WINDOW
    //

    QWidget *container = new QWidget;

    container->setWindowTitle(
        "Vessel 3D Viewer"
    );

    QVBoxLayout *layout =
        new QVBoxLayout(container);

    layout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    Vessel3DWidget *vessel =
        new Vessel3DWidget;

    layout->addWidget(vessel);

    container->resize(900, 700);

    container->show();

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
                // UPDATE 3D VESSEL
                //

                vessel->setOrientation(

                    packet.roll,

                    packet.pitch,

                    packet.yaw
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
    // DELAYED SERIAL START
    //


    //
    // START APPLICATION
    //

    return app.exec();
}