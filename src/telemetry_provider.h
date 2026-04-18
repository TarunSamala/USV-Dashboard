#pragma once 

#include <QObject>
#include <QTimer>

class TelemetryProvider : public QObject {
    Q_OBJECT

    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double battery READ battery NOTIFY batteryChanged)

public:
    explicit TelemetryProvider(QObject* parent = nullptr);

    double speed() const { return m_speed; }
    double battery() const { return m_battery; }
    
signals:
    void speedChanged();
    void batteryChanged();

private:
    QTimer m_timer;

    double m_battery = 100.0;
    double m_speed = 0.0;

    void updateData();
};

