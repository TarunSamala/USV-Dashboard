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

void SerialReader::start(
    const QString& portName
)
{
    //
    // Safety check
    //

    if (portName.isEmpty())
    {
        emit serialError(
            "No serial port selected"
        );

        return;
    }

    //
    // Close existing connection
    //

    if (m_serial.isOpen())
        m_serial.close();

    //
    // Clear old buffered data
    //

    m_buffer.clear();

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

    qDebug() << "Serial connected:"
             << portName;

    emit serialConnected();

    //
    // Allow ESP32 USB CDC to stabilize
    //

    QThread::msleep(1200);

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

    //
    // Close serial
    //

    m_serial.close();

    //
    // Clear packet buffer
    //

    m_buffer.clear();

    qDebug() << "Serial disconnected";

    emit serialDisconnected();
}

void SerialReader::connectPort(
    const QString& portName
)
{
    qDebug() << "Connecting to:"
             << portName;

    start(portName);
}

void SerialReader::disconnectPort()
{
    qDebug() << "Disconnect requested";

    stop();
}

void SerialReader::sendLine(
    const QString& line
)
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