#include "event_logger.h"

#include <QDateTime>

EventLogger::EventLogger(QObject* parent)
    : QObject(parent)
{
}

QStringList EventLogger::logs() const
{
    return m_logs;
}

void EventLogger::addLog(
    const QString& message
)
{
    QString timestamp =
        QDateTime::currentDateTime()
        .toString("hh:mm:ss");

    QString formatted =
        "[" + timestamp + "] " + message;

    m_logs.prepend(formatted);

    if (m_logs.size() > 200)
        m_logs.removeLast();

    emit logsChanged();
}