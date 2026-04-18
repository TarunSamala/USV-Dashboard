#pragma once

#include <QObject>
#include <QTimer>

class DepthModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(double depthRaw READ depthRaw NOTIFY dataChanged)
    Q_PROPERTY(double depthCorrected READ depthCorrected NOTIFY dataChanged)

public:
    explicit DepthModel(QObject* parent = nullptr);

    double depthRaw() const;
    double depthCorrected() const;

signals:
    void dataChanged();

private:
    QTimer m_timer;

    double m_depthRaw = 0.0;
    double m_depthCorrected = 0.0;

    void updateData();

};