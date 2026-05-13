#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "models/telemetry_provider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    TelemetryProvider telemetry;

    engine.rootContext()->setContextProperty(
        "telemetry",
        &telemetry
    );

    engine.loadFromModule("Dashboard", "Main");

    return app.exec();
}