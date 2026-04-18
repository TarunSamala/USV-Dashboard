#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include "models/power_model.h"
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


    PowerModel powerModel;
    engine.rootContext()->setContextProperty("powerModel", &powerModel);
    engine.loadFromModule("Dashboard", "Main");

    return app.exec();
}