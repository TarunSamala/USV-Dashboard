#pragma once

#include <QOpenGLWindow>

#include <QOpenGLFunctions>

class Vessel3DWidget
    : public QOpenGLWindow,
      protected QOpenGLFunctions
{
    Q_OBJECT

public:

    explicit Vessel3DWidget(
        QWindow* parent = nullptr
    );

    void setOrientation(
        float roll,
        float pitch,
        float yaw
    );

protected:

    void initializeGL() override;

    void resizeGL(
        int w,
        int h
    ) override;

    void paintGL() override;

private:

    float m_roll;

    float m_pitch;

    float m_yaw;
};