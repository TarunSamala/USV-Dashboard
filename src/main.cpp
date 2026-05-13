#include <QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QWidget>
#include <QVBoxLayout>

#include <QDebug>
#include <QTimer>

#include "widgets/Vessel3DWidget.h"

#include "models/telemetry_provider.h"
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

    //
    // SERIAL DEBUG PIPELINE
    //

    QObject::connect(
        &serialReader,
        &SerialReader::lineReceived,
        [&](const QString& line)
        {
            qDebug() << "LINE:" << line;

            logger.addLog(line);
        }
    );

    QObject::connect(
        &serialReader,
        &SerialReader::serialConnected,
        [&]()
        {
            logger.addLog(
                "ESP32 serial connected"
            );
        }
    );

    QObject::connect(
        &serialReader,
        &SerialReader::serialDisconnected,
        [&]()
        {
            logger.addLog(
                "ESP32 serial disconnected"
            );
        }
    );

    QObject::connect(
        &serialReader,
        &SerialReader::serialError,
        [&](const QString& error)
        {
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
    // DELAYED SERIAL START
    //

    QTimer::singleShot(
        2000,
        [&]()
        {
            logger.addLog(
                "Opening serial port: /dev/ttyACM0"
            );

            serialReader.start(
                "/dev/ttyACM0"
            );
        }
    );

    //
    // START APPLICATION
    //

    return app.exec();
}