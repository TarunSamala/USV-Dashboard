#pragma once

#include <QObject>
#include <QTimer>

class TelemetryModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double roll READ roll NOTIFY dataChanged)
    Q_PROPERTY(double pitch READ pitch NOTIFY dataChanged)
    Q_PROPERTY(double yaw READ yaw NOTIFY dataChanged)

public:
    explicit TelemetryModel(QObject* parent = nullptr);

    double roll() const;
    double pitch() const;
    double yaw() const;

signals:
    void dataChanged();

private:
    QTimer m_timer;

    double m_roll = 0.0;
    double m_pitch = 0.0;
    double m_yaw = 0.0;

    void updateData();
};