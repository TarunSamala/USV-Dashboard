#include "VesselRenderer.h"
#include "VesselItem.h"

#include <QOpenGLFramebufferObject>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

VesselRenderer::VesselRenderer(
    VesselItem* item
)
{
    Q_UNUSED(item);

    initializeOpenGLFunctions();
}

void VesselRenderer::synchronize(
    QQuickFramebufferObject* item
)
{
    VesselItem* vessel =
        static_cast<VesselItem*>(item);

    m_roll  = vessel->roll();
    m_pitch = vessel->pitch();
    m_yaw   = vessel->yaw();
}

void VesselRenderer::render()
{
    const QSize size =
        framebufferObject()->size();

    glViewport(
        0,
        0,
        size.width(),
        size.height()
    );

    glEnable(GL_DEPTH_TEST);

    //
    // BACKGROUND
    //

    glClearColor(
        0.04f,
        0.04f,
        0.045f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    //
    // PROJECTION
    //

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    const float aspect =
        float(size.width())
        /
        float(size.height());

    gluPerspective(
        45.0,
        aspect,
        0.1,
        200.0
    );

    //
    // FIXED CAMERA
    //

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(
    -6.0,
     0.0,
     2.5,

     2.0,
     0.0,
     0.0,

     0.0,
     0.0,
     1.0
);

    drawGrid();

    drawWorldAxes();

    drawVessel();

    update();
}

void VesselRenderer::drawGrid()
{

    //
    // GRID
    //

    glLineWidth(1.0f);

    for (int i = -50; i <= 50; ++i)
    {
        if (i == 0)
            glColor3f(0.24f, 0.24f, 0.24f);
        else
            glColor3f(0.12f, 0.12f, 0.12f);

        glBegin(GL_LINES);

        glVertex3f(-50.0f, 0.0f, (float)i);
        glVertex3f( 50.0f, 0.0f, (float)i);

        glVertex3f((float)i, 0.0f, -50.0f);
        glVertex3f((float)i, 0.0f,  50.0f);

        glEnd();
    }
}

void VesselRenderer::drawWorldAxes()
{
    glLineWidth(3.0f);

    glBegin(GL_LINES);

    // X FORWARD

    glColor3f(
        1.0f,
        0.23f,
        0.18f
    );

    glVertex3f(0,0,0);
    glVertex3f(3,0,0);

    // Y RIGHT

    glColor3f(
        0.45f,
        0.45f,
        0.45f
    );

    glVertex3f(0,0,0);
    glVertex3f(0,3,0);

    // Z UP

    glColor3f(
        0.85f,
        0.85f,
        0.85f
    );

    glVertex3f(0,0,0);
    glVertex3f(0,0,3);

    glEnd();
}

void VesselRenderer::drawVessel()
{
    glPushMatrix();

    //
    // BODY FRAME
    //
    // X = FORWARD
    // Y = RIGHT
    // Z = UP
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
       -m_roll,
        1.0f,
        0.0f,
        0.0f
    );

    //
    // MAIN HULL
    //

    glColor3f(
        0.20f,
        0.20f,
        0.22f
    );

    glBegin(GL_QUADS);

    // TOP

    glVertex3f(-1.00f,-0.35f, 0.10f);
    glVertex3f( 1.20f,-0.35f, 0.10f);
    glVertex3f( 1.20f, 0.35f, 0.10f);
    glVertex3f(-1.00f, 0.35f, 0.10f);

    // BOTTOM

    glVertex3f(-1.00f,-0.35f,-0.10f);
    glVertex3f( 1.20f,-0.35f,-0.10f);
    glVertex3f( 1.20f, 0.35f,-0.10f);
    glVertex3f(-1.00f, 0.35f,-0.10f);

    glEnd();

    //
    // BOW
    //

    glColor3f(
        0.30f,
        0.30f,
        0.32f
    );

    glBegin(GL_TRIANGLES);

    glVertex3f(1.80f,0.0f,0.0f);
    glVertex3f(1.20f,-0.35f,0.10f);
    glVertex3f(1.20f, 0.35f,0.10f);

    glVertex3f(1.80f,0.0f,0.0f);
    glVertex3f(1.20f,-0.35f,-0.10f);
    glVertex3f(1.20f, 0.35f,-0.10f);

    glEnd();

    //
    // CENTERLINE
    //

    glLineWidth(4.0f);

    glColor3f(
        1.0f,
        0.23f,
        0.18f
    );

    glBegin(GL_LINES);

    glVertex3f(
       -0.80f,
        0.0f,
        0.15f
    );

    glVertex3f(
        1.75f,
        0.0f,
        0.15f
    );

    glEnd();

    //
    // BOW MARKER
    //

    glPointSize(10.0f);

    glColor3f(
        1.0f,
        0.23f,
        0.18f
    );

    glBegin(GL_POINTS);

    glVertex3f(
        1.80f,
        0.0f,
        0.18f
    );

    glEnd();

    glPopMatrix();
}