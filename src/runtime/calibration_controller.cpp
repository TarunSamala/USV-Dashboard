#include "calibration_controller.h"

CalibrationController::CalibrationController(
    QObject* parent
)
    : QObject(parent)
{
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

void CalibrationController::processLine(
    const QString& line
)
{
    //
    // GYRO START
    //

    if (
        line.startsWith(
            "CAL:GYRO:START"
        )
    )
    {
        m_active = true;

        m_title =
            "CALIBRATING GYRO";

        m_progress = 0;

        emit activeChanged();
        emit titleChanged();
        emit progressChanged();

        return;
    }

    //
    // MAG START
    //

    if (
        line.startsWith(
            "CAL:MAG:START"
        )
    )
    {
        m_active = true;

        m_title =
            "CALIBRATING MAG";

        m_progress = 0;

        emit activeChanged();
        emit titleChanged();
        emit progressChanged();

        return;
    }

    //
    // BOW START
    //

    if (
        line.startsWith(
            "BOW:START"
        )
    )
    {
        m_active = true;

        m_title =
            "SETTING BOW";

        m_progress = 0;

        emit activeChanged();
        emit titleChanged();
        emit progressChanged();

        return;
    }

    //
    // INFO
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
    // PROGRESS
    //

    if (
        line.contains(":PROG:")
    )
    {
        QString value =
            line.section(
                ":PROG:",
                1,
                1
            );

        //
        // HANDLE:
        // CAL:MAG:PROG:52,MX:...
        //

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
    // DONE
    //

    if (
        line.contains(":DONE")
        ||
        line.startsWith("BOW:OK")
    )
    {
        m_progress = 100;

        emit progressChanged();

        m_instruction =
            "Operation completed successfully";

        emit instructionChanged();

        m_active = false;

        emit activeChanged();

        return;
    }

    //
    // ERROR
    //

    if (
        line.contains(":ERR:")
    )
    {
        m_instruction =
            line;

        emit instructionChanged();

        m_active = false;

        emit activeChanged();

        return;
    }
}