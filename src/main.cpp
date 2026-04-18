#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include "telemetry_provider.h"
#include <QQmlContext>

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


    TelemetryProvider telemetry;
    engine.rootContext()->setContextProperty("telemetry", &telemetry);
    engine.loadFromModule("Dashboard", "Main");

    return app.exec();
}