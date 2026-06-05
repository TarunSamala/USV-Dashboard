#pragma once

#include <QObject>  
#include <QTimer>

class CalibrationController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        bool active
        READ active
        NOTIFY activeChanged
    )

    Q_PROPERTY(
        QString title
        READ title
        NOTIFY titleChanged
    )

    Q_PROPERTY(
        QString instruction
        READ instruction
        NOTIFY instructionChanged
    )

    Q_PROPERTY(
        int progress
        READ progress
        NOTIFY progressChanged
    )

    Q_PROPERTY(
        bool success
        READ success
        NOTIFY successChanged
    )

    Q_PROPERTY(
        QString warning
        READ warning
        NOTIFY warningChanged
    )

    Q_PROPERTY(
        QString error
        READ error
        NOTIFY errorChanged
    )

public:

    explicit CalibrationController(
        QObject* parent = nullptr
    );

    bool active() const;

    QString title() const;

    QString instruction() const;

    int progress() const;

    bool success() const;

    QString warning() const;

    QString error() const;

    void processLine(
        const QString& line
    );

signals:

    void activeChanged();

    void titleChanged();

    void instructionChanged();

    void progressChanged();

    void successChanged();

    void warningChanged();

    void errorChanged();

    void calibrationFinished();

private:

    bool m_active = false;

    QString m_title;

    QString m_instruction;

    int m_progress = 0;

    bool m_success = false;

    QString m_warning;

    QString m_error;

    QTimer m_magTimer;
};