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
    // IMU
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
    // CLEAR
    //

    glClearColor(
        0.02f,
        0.02f,
        0.02f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT
        |
        GL_DEPTH_BUFFER_BIT
    );

    glEnable(GL_DEPTH_TEST);

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
        35.0,
        aspect,
        0.1,
        100.0
    );

    //
    // CAMERA
    //
    // TRUE 360 CAMERA
    // NO ANGLE LIMITS
    //

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //
    // CAMERA DISTANCE
    //

    glTranslatef(
        0.0f,
        0.0f,
       -m_cameraDistance
    );

    //
    // CAMERA ROTATION
    //

    glRotatef(
        m_cameraPitch,
        1.0f,
        0.0f,
        0.0f
    );

    glRotatef(
        m_cameraYaw,
        0.0f,
        1.0f,
        0.0f
    );

    //
    // GRID
    //

    glLineWidth(1.0f);

    glColor3f(
        0.06f,
        0.06f,
        0.06f
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
    // ====================================
    // IMU BOX
    // ====================================
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
    // BOX COLOR
    //

    glColor3f(
        0.40f,
        0.40f,
        0.40f
    );

    glBegin(GL_QUADS);

    //
    // TOP
    //

    glVertex3f(-0.6f,  0.15f, -0.45f);
    glVertex3f( 0.6f,  0.15f, -0.45f);
    glVertex3f( 0.6f,  0.15f,  0.45f);
    glVertex3f(-0.6f,  0.15f,  0.45f);

    //
    // BOTTOM
    //

    glVertex3f(-0.6f, -0.15f, -0.45f);
    glVertex3f( 0.6f, -0.15f, -0.45f);
    glVertex3f( 0.6f, -0.15f,  0.45f);
    glVertex3f(-0.6f, -0.15f,  0.45f);

    //
    // FRONT
    //

    glVertex3f(-0.6f, -0.15f, 0.45f);
    glVertex3f(-0.6f,  0.15f, 0.45f);
    glVertex3f( 0.6f,  0.15f, 0.45f);
    glVertex3f( 0.6f, -0.15f, 0.45f);

    //
    // BACK
    //

    glVertex3f(-0.6f, -0.15f, -0.45f);
    glVertex3f(-0.6f,  0.15f, -0.45f);
    glVertex3f( 0.6f,  0.15f, -0.45f);
    glVertex3f( 0.6f, -0.15f, -0.45f);

    //
    // LEFT
    //

    glVertex3f(-0.6f, -0.15f, -0.45f);
    glVertex3f(-0.6f,  0.15f, -0.45f);
    glVertex3f(-0.6f,  0.15f,  0.45f);
    glVertex3f(-0.6f, -0.15f,  0.45f);

    //
    // RIGHT
    //

    glVertex3f(0.6f, -0.15f, -0.45f);
    glVertex3f(0.6f,  0.15f, -0.45f);
    glVertex3f(0.6f,  0.15f,  0.45f);
    glVertex3f(0.6f, -0.15f,  0.45f);

    glEnd();

    //
    // ====================================
    // RED BOW ARROW
    // ON TOP OF BOX
    // POINTING AWAY
    // ====================================
    //

    glLineWidth(4.0f);

    glColor3f(
        1.0f,
        0.0f,
        0.0f
    );

    glBegin(GL_LINES);

    //
    // MAIN SHAFT
    //

    glVertex3f(
        0.0f,
        0.20f,
        0.0f
    );

    glVertex3f(
        0.0f,
        0.20f,
       -0.85f
    );

    //
    // LEFT HEAD
    //

    glVertex3f(
        0.0f,
        0.20f,
       -0.85f
    );

    glVertex3f(
       -0.10f,
        0.20f,
       -0.68f
    );

    //
    // RIGHT HEAD
    //

    glVertex3f(
        0.0f,
        0.20f,
       -0.85f
    );

    glVertex3f(
        0.10f,
        0.20f,
       -0.68f
    );

    glEnd();

    //
    // END IMU
    //

    glPopMatrix();

    //
    // CONTINUOUS UPDATE
    //

    update();
}