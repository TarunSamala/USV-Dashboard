#include "telemetry_model.h"

#include <cstdlib>

TelemetryModel::TelemetryModel(QObject* parent)
    : QObject(parent)
{
    connect(
        &m_timer,
        &QTimer::timeout,
        this,
        &TelemetryModel::updateData
    );

    m_timer.start(500);
}

double TelemetryModel::roll() const
{
    return m_roll;
}

double TelemetryModel::pitch() const
{
    return m_pitch;
}

double TelemetryModel::yaw() const
{
    return m_yaw;
}

void TelemetryModel::updateData()
{
    m_roll = (std::rand() % 60) - 30;

    m_pitch = (std::rand() % 40) - 20;

    m_yaw = std::rand() % 360;

    emit dataChanged();
}