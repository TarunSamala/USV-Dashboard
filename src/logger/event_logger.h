#pragma once

#include <QObject>

#include <QStringList>

class EventLogger : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        QStringList logs
        READ logs
        NOTIFY logsChanged
    )

public:

    explicit EventLogger(
        QObject* parent = nullptr
    );

    QStringList logs() const;

    Q_INVOKABLE void addLog(
        const QString& message
    );

signals:

    void logsChanged();

private:

    QStringList m_logs;
};