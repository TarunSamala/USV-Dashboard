#pragma once

#include <QObject>

class CalibrationController
    : public QObject
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

public:

    explicit CalibrationController(
        QObject* parent = nullptr
    );

    //
    // STATE
    //

    bool active() const;

    QString title() const;

    QString instruction() const;

    int progress() const;

    //
    // SERIAL EVENT PROCESSOR
    //

    void processLine(
        const QString& line
    );

signals:

    void activeChanged();

    void titleChanged();

    void instructionChanged();

    void progressChanged();

private:

    bool m_active = false;

    QString m_title =
        "IDLE";

    QString m_instruction =
        "Waiting for operation";

    int m_progress = 0;
};