#include "system_logger.h"

#include <QDateTime>

SystemLogger::SystemLogger(
    QObject* parent
)
    : QObject(parent)
{
}

QStringList SystemLogger::logs() const
{
    return m_logs;
}

void SystemLogger::addLog(
    const QString& message
)
{
    QString timestamp =
        QDateTime::currentDateTime()
        .toString("[hh:mm:ss] ");

    m_logs.prepend(
        timestamp + message
    );

    while (m_logs.size() > 100)
    {
        m_logs.removeLast();
    }

    emit logsChanged();
}