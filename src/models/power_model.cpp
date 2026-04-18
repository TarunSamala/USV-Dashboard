#include "power_model.h"
#include <cstdlib>

PowerModel::PowerModel(QObject* parent)
    : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &PowerModel::updateData);
    m_timer.start(1000);
}

double PowerModel::speed() const { return m_speed; }
double PowerModel::speedKnots() const { return m_speed * 0.539957; }
double PowerModel::battery() const { return m_battery; }
QVector<double> PowerModel::powerHistory() const { return m_powerHistory; }

void PowerModel::updateData()
{
    m_speed = std::rand() % 50;
    m_battery -= 0.1;

    if (m_battery < 0)
        m_battery = 100;

    double power = m_speed * 2.5;

    m_powerHistory.append(power);

    if (m_powerHistory.size() > 100)
        m_powerHistory.remove(0);

    emit dataChanged();
}