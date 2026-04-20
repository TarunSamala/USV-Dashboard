#pragma once

#include <QObject>
#include <QSerialPort>

class SerialReader : public QObject {
    Q_OBJECT

public:
    explicit SerialReader(QObject* parent = nullptr);

    void start(const QString& portName);

signals:
    void dataReceived(const QString& data); 

private:
    QSerialPort m_serial;

private slots:
    void readData();
};