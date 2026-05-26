
#include "serial_reader.h"

#include <QDebug>

#include <QTimer>

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
            if (
                error ==
                QSerialPort::NoError
            )
            {
                return;
            }

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
    // VALIDATION
    //

    if (portName.isEmpty())
    {
        emit serialError(
            "No serial port selected"
        );

        return;
    }

    //
    // CLOSE OLD PORT
    //

    if (m_serial.isOpen())
    {
        m_serial.close();
    }

    //
    // CLEAR BUFFER
    //

    m_buffer.clear();

    //
    // CONFIGURE SERIAL
    //

    m_serial.setPortName(
        portName
    );

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
    // VERY IMPORTANT
    // PREVENT ESP32 RESET
    //

    m_serial.setDataTerminalReady(
        false
    );

    m_serial.setRequestToSend(
        false
    );

    //
    // OPEN PORT
    //

    if (
        !m_serial.open(
            QIODevice::ReadWrite
        )
    )
    {
        emit serialError(
            "Failed to open serial port: "
            + m_serial.errorString()
        );

        return;
    }

    qDebug()
        << "Serial connected:"
        << portName;

    emit serialConnected();

    //
    // WAIT FOR STABLE USB CDC
    //

    QTimer::singleShot(
        1500,
        this,
        [this]()
        {
            if (!m_serial.isOpen())
                return;

            //
            // ONLY SEND
            // AFTER STABLE
            //

            sendLine(
                "CONNECT:DASHBOARD"
            );

            sendLine(
                "START"
            );

            qDebug()
                << "Handshake sent";
        }
    );
}

void SerialReader::stop()
{
    if (!m_serial.isOpen())
        return;

    //
    // CLOSE PORT
    //

    m_serial.close();

    //
    // CLEAR BUFFER
    //

    m_buffer.clear();

    qDebug()
        << "Serial disconnected";

    emit serialDisconnected();
}

void SerialReader::connectPort(
    const QString& portName
)
{
    qDebug()
        << "Connecting to:"
        << portName;

    start(portName);
}

void SerialReader::disconnectPort()
{
    qDebug()
        << "Disconnect requested";

    stop();
}

void SerialReader::sendLine(
    const QString& line
)
{
    if (!m_serial.isOpen())
        return;

    QByteArray data =
        line.toUtf8()
        + '\n';

    m_serial.write(data);

    m_serial.flush();

    qDebug()
        << "TX:"
        << line;
}

void SerialReader::readData()
{
    //
    // APPEND BYTES
    //

    m_buffer += QString::fromUtf8(
        m_serial.readAll()
    );

    //
    // COMPLETE LINES ONLY
    //

    while (
        m_buffer.contains('\n')
    )
    {
        int newlineIndex =
            m_buffer.indexOf('\n');

        QString line =
            m_buffer.left(
                newlineIndex
            ).trimmed();

        //
        // REMOVE LINE
        //

        m_buffer.remove(
            0,
            newlineIndex + 1
        );

        //
        // IGNORE EMPTY
        //

        if (line.isEmpty())
            continue;

        qDebug()
            << "RX:"
            << line;

        emit lineReceived(line);
    }
}

