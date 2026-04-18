#include "depth_model.h"
#include <cstdlib>

DepthModel::DepthModel(QObject* parent)
    : QObject(parent){

    connect(&m_timer, &QTimer::timeout, this, &DepthModel::updateData);
    m_timer.start(1000);
    }

double DepthModel::depthRaw() const { return m_depthRaw; }
double DepthModel::depthCorrected() const { return m_depthCorrected; }

void DepthModel::updateData(){

    m_depthRaw = 4.0 + (std::rand() % 100) / 100.0;

    m_depthCorrected = m_depthRaw + 0.1;

    emit dataChanged();


}