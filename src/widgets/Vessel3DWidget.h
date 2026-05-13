
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class Vessel3DWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit Vessel3DWidget(QWidget *parent = nullptr);

    void setOrientation(float roll, float pitch, float yaw);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    float m_roll;
    float m_pitch;
    float m_yaw;
};
