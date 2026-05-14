#pragma once

#include <QObject>

#include <QStringList>

class SystemLogger : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        QStringList logs
        READ logs
        NOTIFY logsChanged
    )

public:

    explicit SystemLogger(
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