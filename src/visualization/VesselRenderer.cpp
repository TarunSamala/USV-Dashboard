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
        0.0, 4.5, 8.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    drawGrid();

    drawWorldAxes();

    drawVessel();

    update();
}

void VesselRenderer::drawGrid()
{
    //
    // WATER PLANE
    //

    glColor3f(
        0.08f,
        0.08f,
        0.09f
    );

    glBegin(GL_QUADS);

    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);

    glEnd();

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
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    //
    // FORWARD
    //

    glColor3f(
        0.7f,
        0.15f,
        0.15f
    );

    glVertex3f(0,0,0);
    glVertex3f(3,0,0);

    //
    // UP
    //

    glColor3f(
        0.75f,
        0.75f,
        0.75f
    );

    glVertex3f(0,0,0);
    glVertex3f(0,3,0);

    //
    // LATERAL
    //

    glColor3f(
        0.35f,
        0.35f,
        0.35f
    );

    glVertex3f(0,0,0);
    glVertex3f(0,0,3);

    glEnd();
}

void VesselRenderer::drawVessel()
{
    glPushMatrix();

    //
    // TELEMETRY ORIENTATION
    //
    // Firmware outputs:
    // Roll/Pitch/Yaw
    // through Madgwick fusion.
    //

    glRotatef(
        m_yaw,
        0.0f,
        1.0f,
        0.0f
    );

    glRotatef(
        m_pitch,
        1.0f,
        0.0f,
        0.0f
    );

    glRotatef(
        -m_roll,
        0.0f,
        0.0f,
        1.0f
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

    // Deck

    glVertex3f(-0.45f,  0.10f, -1.40f);
    glVertex3f( 0.45f,  0.10f, -1.40f);
    glVertex3f( 0.45f,  0.10f,  1.00f);
    glVertex3f(-0.45f,  0.10f,  1.00f);

    // Bottom

    glVertex3f(-0.45f, -0.10f, -1.40f);
    glVertex3f( 0.45f, -0.10f, -1.40f);
    glVertex3f( 0.45f, -0.10f,  1.00f);
    glVertex3f(-0.45f, -0.10f,  1.00f);

    glEnd();

    //
    // BOW SECTION
    //

    glColor3f(
        0.28f,
        0.28f,
        0.30f
    );

    glBegin(GL_TRIANGLES);

    glVertex3f(0.0f,  0.10f, -2.00f);
    glVertex3f(-0.45f, 0.10f, -1.40f);
    glVertex3f(0.45f,  0.10f, -1.40f);

    glVertex3f(0.0f, -0.10f, -2.00f);
    glVertex3f(-0.45f,-0.10f, -1.40f);
    glVertex3f(0.45f, -0.10f, -1.40f);

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
        0.0f,
        0.16f,
        0.9f
    );

    glVertex3f(
        0.0f,
        0.16f,
       -1.9f
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
        0.0f,
        0.18f,
       -2.0f
    );

    glEnd();

    glPopMatrix();
}