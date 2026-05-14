#pragma once

#include <QObject>

#include <QFile>

#include <QTextStream>

#include "models/telemetry_packet.h"

class CsvLogger : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        bool logging
        READ isLogging
        NOTIFY loggingChanged
    )

    Q_PROPERTY(
        QString currentFilePath
        READ currentFilePath
        NOTIFY loggingChanged
    )

public:

    explicit CsvLogger(
        QObject* parent = nullptr
    );

    Q_INVOKABLE bool startLogging();

    Q_INVOKABLE void stopLogging();

    bool isLogging() const;

    void logPacket(
        const TelemetryPacket& packet
    );

    QString currentFilePath() const;

signals:

    void loggingChanged();

private:

    QFile m_file;

    QTextStream m_stream;

    bool m_logging = false;

    QString m_filePath;
};