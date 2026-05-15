#pragma once

#include <QObject>

#include <QSerialPort>

class SerialReader : public QObject
{
    Q_OBJECT

public:

    explicit SerialReader(
        QObject* parent = nullptr
    );

    //
    // SERIAL CONTROL
    //

    void start(
        const QString& portName
    );

    void stop();

    //
    // COMMAND TX
    //

    Q_INVOKABLE void sendLine(
        const QString& line
    );

    //
    // QML CONNECTION API
    //

    Q_INVOKABLE void connectPort(
        const QString& portName
    );

    Q_INVOKABLE void disconnectPort();

signals:

    //
    // COMPLETE LINES ONLY
    //

    void lineReceived(
        const QString& line
    );

    void serialConnected();

    void serialDisconnected();

    void serialError(
        const QString& error
    );

private slots:

    void readData();

private:

    QSerialPort m_serial;

    QString m_buffer;
};