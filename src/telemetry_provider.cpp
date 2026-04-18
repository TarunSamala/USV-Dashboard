#include "telemetry_provider.h"
#include <cstdlib>


TelemetryProvider::TelemetryProvider(QObject* parent)
    : QObject(parent){

connect(&m_timer, &QTimer::timeout, this, &TelemetryProvider::updateData);
m_timer.start(500);
    }


void TelemetryProvider::updateData(){
    m_speed = (std::rand() %50);
    m_battery -= 0.1;

    if(m_battery < 0) 
        m_battery = 100;

    emit speedChanged();
    emit batteryChanged();
}

