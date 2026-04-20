#include "serial_reader.h"
#include <QDebug>

SerialReader::SerialReader(QObject* parent)
    : QObject(parent)
{
    connect(&m_serial, &QSerialPort::readyRead,
            this, &SerialReader::readData);
}

void SerialReader::start(const QString& portName)
{
    m_serial.setPortName(portName);
    m_serial.setBaudRate(QSerialPort::Baud115200);

    if (!m_serial.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open serial port:" << m_serial.errorString();
    }
}

void SerialReader::readData()
{
    QByteArray raw = m_serial.readAll();
    QString data = QString::fromUtf8(raw);

    emit dataReceived(data);
}