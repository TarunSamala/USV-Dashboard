
#include "Vessel3DWidget.h"

#include <QPainter>
#include <QMatrix4x4>
#include <QtMath>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

Vessel3DWidget::Vessel3DWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_roll(0.0f),
      m_pitch(0.0f),
      m_yaw(0.0f)
{
}

void Vessel3DWidget::setOrientation(float roll, float pitch, float yaw)
{
    m_roll = roll;
    m_pitch = pitch;
    m_yaw = yaw;

    update();
}

void Vessel3DWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
}

void Vessel3DWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Vessel3DWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        45.0,
        float(width()) / float(height()),
        0.1,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -6.0f);

    // Orientation
    glRotatef(m_yaw,   0.0f, 0.0f, 1.0f);
    glRotatef(m_pitch, 0.0f, 1.0f, 0.0f);
    glRotatef(m_roll,  1.0f, 0.0f, 0.0f);

    // Simple vessel body
    glBegin(GL_QUADS);

    // Top
    glColor3f(0.0f, 0.7f, 1.0f);

    glVertex3f(-1.0f, -0.3f,  0.3f);
    glVertex3f( 1.0f, -0.3f,  0.3f);
    glVertex3f( 1.0f,  0.3f,  0.3f);
    glVertex3f(-1.0f,  0.3f,  0.3f);

    // Bottom
    glColor3f(0.0f, 0.3f, 0.6f);

    glVertex3f(-1.0f, -0.3f, -0.3f);
    glVertex3f(-1.0f,  0.3f, -0.3f);
    glVertex3f( 1.0f,  0.3f, -0.3f);
    glVertex3f( 1.0f, -0.3f, -0.3f);

    glEnd();
}

