#include "csv_logger.h"

#include <QDateTime>

#include <QDir>

#include <QDebug>

CsvLogger::CsvLogger(QObject* parent)
    : QObject(parent)
{
}

bool CsvLogger::startLogging()
{
    //
    // Create logs directory
    //
    if(m_logging)
        return true;

    QDir().mkpath("logs");

    //
    // Timestamped filename
    //

    QString timestamp =
        QDateTime::currentDateTime()
        .toString("yyyyMMdd_hhmmss");

    m_filePath =
        "logs/telemetry_" +
        timestamp +
        ".csv";

    m_file.setFileName(
        m_filePath
    );

    if (
        !m_file.open(
            QIODevice::WriteOnly
            |
            QIODevice::Text
        )
    )
    {
        qWarning()
            << "Failed to create CSV log";

        return false;
    }

    m_stream.setDevice(&m_file);

    //
    // CSV HEADER
    //

    m_stream
        << "timestamp,"
        << "roll,pitch,yaw,"
        << "ax,ay,az,"
        << "gx,gy,gz,"
        << "mx,my,mz,"
        << "temperature\n";

    m_stream.flush();

    m_logging = true;

    qDebug()
        << "CSV logging started:"
        << m_filePath;

    emit loggingChanged();

    return true;
}

void CsvLogger::stopLogging()
{
    if (!m_logging)
        return;

    m_stream.flush();

    m_file.close();

    m_logging = false;

    qDebug()
        << "CSV logging stopped";

    emit loggingChanged();
}

bool CsvLogger::isLogging() const
{
    return m_logging;
}

QString CsvLogger::currentFilePath() const
{
    return m_filePath;
}

void CsvLogger::logPacket(
    const TelemetryPacket& packet
)
{
    if (!m_logging)
        return;

    QString timestamp =
        QDateTime::currentDateTime()
        .toString(Qt::ISODate);

    m_stream
        << timestamp << ","

        << packet.roll << ","
        << packet.pitch << ","
        << packet.yaw << ","

        << packet.accelX << ","
        << packet.accelY << ","
        << packet.accelZ << ","

        << packet.gyroX << ","
        << packet.gyroY << ","
        << packet.gyroZ << ","

        << packet.magX << ","
        << packet.magY << ","
        << packet.magZ << ","

        << packet.temperature

        << "\n";

    m_stream.flush();
}