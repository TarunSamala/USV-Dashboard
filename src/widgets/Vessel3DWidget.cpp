#include "Vessel3DWidget.h"

#include <QtMath>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

Vessel3DWidget::Vessel3DWidget(
    QWindow* parent
)
    : QOpenGLWindow(
          NoPartialUpdate,
          parent
      ),
      m_roll(0.0f),
      m_pitch(0.0f),
      m_yaw(0.0f)
{
}

void Vessel3DWidget::setOrientation(
    float roll,
    float pitch,
    float yaw
)
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

    glClearColor(
        0.03f,
        0.03f,
        0.03f,
        1.0f
    );
}

void Vessel3DWidget::resizeGL(
    int w,
    int h
)
{
    glViewport(
        0,
        0,
        w,
        h
    );
}

void Vessel3DWidget::paintGL()
{
    glClear(
        GL_COLOR_BUFFER_BIT
        |
        GL_DEPTH_BUFFER_BIT
    );

    //
    // Projection
    //

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(
        45.0,
        float(width()) / float(height()),
        0.1,
        100.0
    );

    //
    // Model View
    //

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //
    // Camera
    //

    glTranslatef(
        0.0f,
        0.0f,
        -8.0f
    );

    //
    // Slight scene tilt
    //

    glRotatef(
        20.0f,
        1.0f,
        0.0f,
        0.0f
    );

    //
    // WORLD AXES
    //

    glLineWidth(2.5f);

    glBegin(GL_LINES);

    //
    // X axis — RED
    //

    glColor3f(1.0f, 0.2f, 0.2f);

    glVertex3f(0,0,0);
    glVertex3f(3,0,0);

    //
    // Y axis — GREEN
    //

    glColor3f(0.2f, 1.0f, 0.2f);

    glVertex3f(0,0,0);
    glVertex3f(0,3,0);

    //
    // Z axis — BLUE
    //

    glColor3f(0.2f, 0.6f, 1.0f);

    glVertex3f(0,0,0);
    glVertex3f(0,0,3);

    glEnd();

    //
    // VEHICLE FRAME
    //

    glPushMatrix();

    //
    // Apply orientation
    //

    glRotatef(
        m_yaw,
        0.0f,
        0.0f,
        1.0f
    );

    glRotatef(
        m_pitch,
        0.0f,
        1.0f,
        0.0f
    );

    glRotatef(
        m_roll,
        1.0f,
        0.0f,
        0.0f
    );

    //
    // BODY AXES
    //

    glLineWidth(4.0f);

    glBegin(GL_LINES);

    //
    // Forward axis
    //

    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex3f(0,0,0);
    glVertex3f(2.0f,0,0);

    //
    // Side axis
    //

    glColor3f(0.0f, 1.0f, 0.0f);

    glVertex3f(0,0,0);
    glVertex3f(0,2.0f,0);

    //
    // Up axis
    //

    glColor3f(0.0f, 0.7f, 1.0f);

    glVertex3f(0,0,0);
    glVertex3f(0,0,2.0f);

    glEnd();

    //
    // Semi-transparent body plane
    //

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glBegin(GL_QUADS);

    //
    // Top face
    //

    glColor4f(
        0.2f,
        0.6f,
        1.0f,
        0.35f
    );

    glVertex3f(-2.0f, -1.0f, 0.0f);
    glVertex3f( 2.0f, -1.0f, 0.0f);
    glVertex3f( 2.0f,  1.0f, 0.0f);
    glVertex3f(-2.0f,  1.0f, 0.0f);

    glEnd();

    //
    // Nose marker
    //

    glBegin(GL_TRIANGLES);

    glColor3f(
        1.0f,
        1.0f,
        0.0f
    );

    glVertex3f(2.4f, 0.0f, 0.0f);
    glVertex3f(1.8f, 0.4f, 0.0f);
    glVertex3f(1.8f,-0.4f, 0.0f);

    glEnd();

    glDisable(GL_BLEND);

    //
    // Center point
    //

    glPointSize(10.0f);

    glBegin(GL_POINTS);

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    glVertex3f(0,0,0);

    glEnd();

    glPopMatrix();
}