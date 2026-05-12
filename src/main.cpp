#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "models/power_model.h"
#include "models/depth_model.h"
#include "serial/serial_reader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(EXIT_FAILURE); },
        Qt::QueuedConnection
    );

    DepthModel depthModel;
    PowerModel powerModel;

    engine.rootContext()->setContextProperty("depthModel", &depthModel);
    engine.rootContext()->setContextProperty("powerModel", &powerModel);

    engine.loadFromModule("Dashboard", "Main");

    SerialReader serial;
    serial.start("/dev/ttyACM0");

    QObject::connect(&serial, &SerialReader::dataReceived,
        [](const QString& data) {
            qDebug() << "Received:" << data;
        });

    return app.exec();
}