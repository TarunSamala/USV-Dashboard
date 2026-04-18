#pragma once

#include <QObject>
#include <QTimer>
#include <QVector>

class PowerModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(double speed READ speed NOTIFY dataChanged)
    Q_PROPERTY(double battery READ battery NOTIFY dataChanged)
    Q_PROPERTY(QVector<double> powerHistory READ powerHistory NOTIFY dataChanged)

public:
    explicit PowerModel(QObject* parent = nullptr);

    double speed() const;
    double battery() const;

    QVector<double> powerHistory() const;

signals:
    void dataChanged();

private:
    QTimer m_timer;

    double m_speed = 0.0;
    double m_battery = 100.0;
    QVector<double> m_powerHistory;

    void updateData();
};