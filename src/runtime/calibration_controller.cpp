
#include "calibration_controller.h"

CalibrationController::CalibrationController(
    QObject* parent
)
    : QObject(parent)
{
    //
    // MAG TIMER
    //

    connect(
        &m_magTimer,
        &QTimer::timeout,
        this,
        [this]()
        {
            if (!m_active)
            {
                m_magTimer.stop();
                return;
            }

            //
            // SMOOTH MAG PROGRESS
            //

            if (m_progress < 15)
            {
                m_progress += 2;

                emit progressChanged();
            }
        }
    );
}

bool CalibrationController::active() const
{
    return m_active;
}

QString CalibrationController::title() const
{
    return m_title;
}

QString CalibrationController::instruction() const
{
    return m_instruction;
}

int CalibrationController::progress() const
{
    return m_progress;
}

bool CalibrationController::success() const
{
    return m_success;
}

QString CalibrationController::warning() const
{
    return m_warning;
}

QString CalibrationController::error() const
{
    return m_error;
}

void CalibrationController::processLine(
    const QString& line
)
{
    //
    // RESET STATUS
    //

    auto resetStatus =
        [this]()
    {
        m_success = false;

        m_warning.clear();

        m_error.clear();

        emit successChanged();

        emit warningChanged();

        emit errorChanged();
    };

    //
    // =========================================
    // GYRO START
    // =========================================
    //

    if (
        line.startsWith(
            "CAL:GYRO:START"
        )
    )
    {
        resetStatus();

        m_active = true;

        m_title =
            "CALIBRATING GYRO";

        m_instruction =
            "Keep module flat and still";

        m_progress = 0;

        emit activeChanged();

        emit titleChanged();

        emit instructionChanged();

        emit progressChanged();

        return;
    }

    //
    // =========================================
    // MAG START
    // =========================================
    //

    if (
        line.startsWith(
            "CAL:MAG:START"
        )
    )
    {
        resetStatus();

        m_active = true;

        m_title =
            "CALIBRATING MAG";

        m_instruction =
            "Rotate module slowly in all directions";

        m_progress = 0;

        //
        // START TIMER
        //

        m_magTimer.start(300);

        emit activeChanged();

        emit titleChanged();

        emit instructionChanged();

        emit progressChanged();

        return;
    }

    //
    // =========================================
    // BOW START
    // =========================================
    //

    if (
        line.startsWith(
            "BOW:START"
        )
    )
    {
        resetStatus();

        m_active = true;

        m_title =
            "SETTING BOW";

        m_instruction =
            "Point module toward vessel bow";

        m_progress = 0;

        emit activeChanged();

        emit titleChanged();

        emit instructionChanged();

        emit progressChanged();

        return;
    }

    //
    // =========================================
    // INFO
    // =========================================
    //

    if (
        line.contains(":INFO:")
    )
    {
        QString info =
            line.section(
                ":INFO:",
                1
            );

        m_instruction =
            info;

        emit instructionChanged();

        return;
    }

    //
    // =========================================
    // GYRO PROGRESS ONLY
    // =========================================
    //

    if (
        line.startsWith(
            "CAL:GYRO:PROG:"
        )
    )
    {
        QString value =
            line.section(
                "CAL:GYRO:PROG:",
                1
            );

        value =
            value.section(
                ",",
                0,
                0
            );

        m_progress =
            value.toInt();

        emit progressChanged();

        return;
    }

    //
    // =========================================
    // WARNINGS
    // =========================================
    //

    if (
        line.contains(
            "insufficient_rotation"
        )
    )
    {
        m_warning =
            "Rotate module more widely";

        emit warningChanged();

        return;
    }

    //
    // =========================================
    // DONE
    // =========================================
    //

    if (
        line.contains(":DONE")
        ||
        line.startsWith("BOW:OK")
    )
    {
        //
        // STOP TIMER
        //

        m_magTimer.stop();

        m_progress = 100;

        emit progressChanged();

        m_instruction =
            "Operation completed successfully";

        emit instructionChanged();

        m_success = true;

        emit successChanged();

        m_active = false;

        emit activeChanged();

        emit calibrationFinished();

        return;
    }

    //
    // =========================================
    // ERROR
    // =========================================
    //

    if (
        line.contains(":ERR:")
    )
    {
        //
        // STOP TIMER
        //

        m_magTimer.stop();

        QString err =
            line.section(
                ":ERR:",
                1
            );

        m_error = err;

        emit errorChanged();

        m_instruction =
            "Operation failed";

        emit instructionChanged();

        m_active = false;

        emit activeChanged();

        return;
    }
}

