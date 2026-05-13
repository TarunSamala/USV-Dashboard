#include "serial_reader.h"

#include <QDebug>

#include <QThread>

SerialReader::SerialReader(QObject* parent)
    : QObject(parent)
{
    connect(
        &m_serial,
        &QSerialPort::readyRead,
        this,
        &SerialReader::readData
    );

    connect(
        &m_serial,
        &QSerialPort::errorOccurred,
        this,
        [this](QSerialPort::SerialPortError error)
        {
            if (error == QSerialPort::NoError)
                return;

            emit serialError(
                m_serial.errorString()
            );
        }
    );
}

void SerialReader::start(const QString& portName)
{
    //
    // Close existing connection
    //

    if (m_serial.isOpen())
        m_serial.close();

    //
    // Configure serial
    //

    m_serial.setPortName(portName);

    m_serial.setBaudRate(
        QSerialPort::Baud115200
    );

    m_serial.setDataBits(
        QSerialPort::Data8
    );

    m_serial.setParity(
        QSerialPort::NoParity
    );

    m_serial.setStopBits(
        QSerialPort::OneStop
    );

    m_serial.setFlowControl(
        QSerialPort::NoFlowControl
    );

    //
    // Prevent ESP32 auto-reset issues
    //

    

    //
    // Open serial
    //

    if (!m_serial.open(QIODevice::ReadWrite))
    {
        emit serialError(
            "Failed to open serial port: "
            + m_serial.errorString()
        );

        return;
    }

    //
    // Prevent ESP32 auto-reset issues
    //

    m_serial.setDataTerminalReady(false);

    m_serial.setRequestToSend(false);

    qDebug() << "Serial connected:"
             << portName;

    emit serialConnected();

    //
    // Allow ESP32-S3 USB CDC to stabilize
    //

    QThread::msleep(1500);

    //
    // Dashboard handshake
    //

    sendLine("CONNECT:DASHBOARD");

    sendLine("START");

    qDebug() << "Handshake sent";
}

void SerialReader::stop()
{
    if (!m_serial.isOpen())
        return;

    m_serial.close();

    qDebug() << "Serial disconnected";

    emit serialDisconnected();
}

void SerialReader::sendLine(const QString& line)
{
    if (!m_serial.isOpen())
        return;

    QByteArray data =
        line.toUtf8() + '\n';

    m_serial.write(data);

    m_serial.flush();

    qDebug() << "TX:" << line;
}

void SerialReader::readData()
{
    //
    // Append incoming bytes
    //

    m_buffer += QString::fromUtf8(
        m_serial.readAll()
    );

    //
    // Process COMPLETE lines only
    //

    while (m_buffer.contains('\n'))
    {
        int newlineIndex =
            m_buffer.indexOf('\n');

        QString line =
            m_buffer.left(
                newlineIndex
            ).trimmed();

        //
        // Remove processed line
        //

        m_buffer.remove(
            0,
            newlineIndex + 1
        );

        //
        // Ignore empty lines
        //

        if (line.isEmpty())
            continue;

        qDebug() << "RX:" << line;

        emit lineReceived(line);
    }
}