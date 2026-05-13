#include <QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QWidget>
#include <QVBoxLayout>

#include <QTimer>
#include <QtMath>

#include "Vessel3DWidget.h"

#include "models/telemetry_provider.h"
#include "logger/event_logger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // BACKEND OBJECTS

    TelemetryProvider telemetry;

    EventLogger logger;

    // QML ENGINE

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(
        "telemetry",
        &telemetry
    );

    engine.rootContext()->setContextProperty(
        "logger",
        &logger
    );

    // INITIAL LOGS

    logger.addLog("Dashboard initialized");

    logger.addLog("Telemetry provider started");

    logger.addLog("Waiting for ESP32 connection");

    // LOAD DASHBOARD

    engine.loadFromModule("Dashboard", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    // TEST OPENGL WINDOW

    QWidget *container = new QWidget;

    container->setWindowTitle("Vessel 3D Viewer");

    QVBoxLayout *layout = new QVBoxLayout(container);

    layout->setContentsMargins(0,0,0,0);

    Vessel3DWidget *vessel = new Vessel3DWidget;

    layout->addWidget(vessel);

    container->resize(900, 700);

    container->show();

    // TEST ANIMATION


    QTimer *timer = new QTimer(container);

    QObject::connect(
        timer,
        &QTimer::timeout,
        [=]() {

            static float angle = 0.0f;

            angle += 1.0f;

            vessel->setOrientation(

                qSin(angle * 0.03f) * 20.0f,   // roll

                qCos(angle * 0.02f) * 15.0f,   // pitch

                angle                           // yaw
            );
        }
    );

    timer->start(16);

    
    // START APP


    return app.exec();
}