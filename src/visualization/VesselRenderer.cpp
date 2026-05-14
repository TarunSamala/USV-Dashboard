
#include "VesselRenderer.h"

#include "VesselItem.h"

#include <QOpenGLFramebufferObject>

#include <QtMath>

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
    QQuickFramebufferObject *item
)
{
    VesselItem* vessel =
        static_cast<VesselItem*>(item);

    //
    // IMU ORIENTATION
    //

    m_roll =
        vessel->roll();

    m_pitch =
        vessel->pitch();

    m_yaw =
        vessel->yaw();

    //
    // CAMERA
    //

    m_cameraYaw =
        vessel->cameraYaw;

    m_cameraPitch =
        vessel->cameraPitch;

    m_cameraDistance =
        vessel->cameraDistance;
}

void VesselRenderer::render()
{
    //
    // FRAMEBUFFER
    //

    const QSize size =
        framebufferObject()->size();

    //
    // VIEWPORT
    //

    glViewport(
        0,
        0,
        size.width(),
        size.height()
    );

    //
    // BACKGROUND
    //

    glClearColor(
        0.02f,
        0.02f,
        0.02f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glEnable(GL_DEPTH_TEST);

    //
    // PROJECTION
    //

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    const float aspect =
        float(size.width()) /
        float(size.height());

    gluPerspective(
        24.0,
        aspect,
        0.1,
        100.0
    );

    //
    // CAMERA
    //

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    const float yawRad =
        qDegreesToRadians(
            m_cameraYaw
        );

    const float pitchRad =
        qDegreesToRadians(
            m_cameraPitch
        );

    const float camX =
        m_cameraDistance
        * cos(pitchRad)
        * sin(yawRad);

    const float camY =
        m_cameraDistance
        * sin(pitchRad);

    const float camZ =
        m_cameraDistance
        * cos(pitchRad)
        * cos(yawRad);

    gluLookAt(

        camX,
        camY,
        camZ,

        0.0,
        0.0,
        0.0,

        0.0,
        1.0,
        0.0
    );

    //
    // GRID
    //

    glLineWidth(1.0f);

    glColor3f(
        0.05f,
        0.05f,
        0.05f
    );

    glBegin(GL_LINES);

    for (int i = -8; i <= 8; ++i)
    {
        //
        // X GRID
        //

        glVertex3f(
            -8.0f,
            0.0f,
            (float)i
        );

        glVertex3f(
             8.0f,
             0.0f,
            (float)i
        );

        //
        // Z GRID
        //

        glVertex3f(
            (float)i,
            0.0f,
            -8.0f
        );

        glVertex3f(
            (float)i,
            0.0f,
             8.0f
        );
    }

    glEnd();

    //
    // STATIC WORLD AXES
    //

    glLineWidth(4.0f);

    glBegin(GL_LINES);

    //
    // X AXIS (RED)
    // FORWARD / AWAY
    //

    glColor3f(
        1.0f,
        0.0f,
        0.0f
    );

    glVertex3f(
        0.0f,
        0.0f,
        0.0f
    );

    glVertex3f(
        0.0f,
        0.0f,
        2.0f
    );

    //
    // Y AXIS (BLUE)
    // RIGHT
    //

    glColor3f(
        0.0f,
        0.45f,
        1.0f
    );

    glVertex3f(
        0.0f,
        0.0f,
        0.0f
    );

    glVertex3f(
        2.0f,
        0.0f,
        0.0f
    );

    //
    // Z AXIS (GREEN)
    // UP
    //

    glColor3f(
        0.0f,
        1.0f,
        0.0f
    );

    glVertex3f(
        0.0f,
        0.0f,
        0.0f
    );

    glVertex3f(
        0.0f,
       -2.0f,
        0.0f
    );

    glEnd();

    //
    // ROTATING BODY FRAME
    //

    glPushMatrix();

    //
    // IMU ROTATION
    //

    glRotatef(
        m_yaw,
        0.0f,
        1.0f,
        0.0f
    );

    glRotatef(
        m_pitch,
        0.0f,
        0.0f,
        1.0f
    );

    glRotatef(
        m_roll,
        1.0f,
        0.0f,
        0.0f
    );

    //
    // IMU BOX
    //

    glColor3f(
        0.35f,
        0.35f,
        0.35f
    );

    glBegin(GL_QUADS);

    //
    // TOP
    //

    glVertex3f(-0.45f,  0.15f, -0.45f);
    glVertex3f( 0.45f,  0.15f, -0.45f);
    glVertex3f( 0.45f,  0.15f,  0.45f);
    glVertex3f(-0.45f,  0.15f,  0.45f);

    //
    // BOTTOM
    //

    glVertex3f(-0.45f, -0.15f, -0.45f);
    glVertex3f( 0.45f, -0.15f, -0.45f);
    glVertex3f( 0.45f, -0.15f,  0.45f);
    glVertex3f(-0.45f, -0.15f,  0.45f);

    //
    // LEFT
    //

    glVertex3f(-0.45f, -0.15f, -0.45f);
    glVertex3f(-0.45f,  0.15f, -0.45f);
    glVertex3f( 0.45f,  0.15f, -0.45f);
    glVertex3f( 0.45f, -0.15f, -0.45f);

    //
    // RIGHT
    //

    glVertex3f(-0.45f, -0.15f, 0.45f);
    glVertex3f(-0.45f,  0.15f, 0.45f);
    glVertex3f( 0.45f,  0.15f, 0.45f);
    glVertex3f( 0.45f, -0.15f, 0.45f);

    glEnd();

    //
    // BOW ARROW
    //

    glLineWidth(2.0f);

    glColor3f(
        0.0f,
        0.0f,
        0.0f
    );

    glBegin(GL_LINES);

    //
    // MAIN SHAFT
    //

    glVertex3f(
        0.0f,
        0.22f,
        0.0f
    );

    glVertex3f(
        0.0f,
        0.22f,
        0.60f
    );

    //
    // LEFT HEAD
    //

    glVertex3f(
        0.0f,
        0.22f,
        0.60f
    );

    glVertex3f(
       -0.08f,
        0.22f,
        0.50f
    );

    //
    // RIGHT HEAD
    //

    glVertex3f(
        0.0f,
        0.22f,
        0.60f
    );

    glVertex3f(
        0.08f,
        0.22f,
        0.50f
    );

    glEnd();

    //
    // END ROTATING FRAME
    //

    glPopMatrix();
}

