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
    QQuickFramebufferObject *item
)
{
    VesselItem* vessel =
        static_cast<VesselItem*>(item);

    m_roll =
        vessel->roll();

    m_pitch =
        vessel->pitch();

    m_yaw =
        vessel->yaw();
}

void VesselRenderer::render()
{
    //
    // FRAMEBUFFER SIZE
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
        26.0,
        aspect,
        0.1,
        100.0
    );

    //
    // CAMERA
    //

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(

    0.0, 8.0, 0.01,

    0.0, 0.0, 0.0,

    0.0, 0.0, -1.0
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
        // DEPTH
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

        //
        // WIDTH
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
    }

    glEnd();

    //
    // VESSEL TRANSFORM
    //

    glPushMatrix();

    //
    // YAW
    //

    glRotatef(
        m_yaw,
        0.0f,
        1.0f,
        0.0f
    );

    //
    // PITCH
    //

    glRotatef(
        m_pitch,
        0.0f,
        0.0f,
        1.0f
    );

    //
    // ROLL
    //

    glRotatef(
        m_roll,
        1.0f,
        0.0f,
        0.0f
    );

    //
    // MAIN BODY
    //

    glColor3f(
        0.38f,
        0.38f,
        0.38f
    );

    glBegin(GL_QUADS);

    //
    // TOP
    //

    glVertex3f(-1.2f,  0.18f, -0.30f);
    glVertex3f( 0.5f,  0.18f, -0.30f);
    glVertex3f( 0.5f,  0.18f,  0.30f);
    glVertex3f(-1.2f,  0.18f,  0.30f);

    //
    // BOTTOM
    //

    glVertex3f(-1.2f, -0.18f, -0.30f);
    glVertex3f( 0.5f, -0.18f, -0.30f);
    glVertex3f( 0.5f, -0.18f,  0.30f);
    glVertex3f(-1.2f, -0.18f,  0.30f);

    //
    // LEFT
    //

    glVertex3f(-1.2f, -0.18f, -0.30f);
    glVertex3f(-1.2f,  0.18f, -0.30f);
    glVertex3f( 0.5f,  0.18f, -0.30f);
    glVertex3f( 0.5f, -0.18f, -0.30f);

    //
    // RIGHT
    //

    glVertex3f(-1.2f, -0.18f, 0.30f);
    glVertex3f(-1.2f,  0.18f, 0.30f);
    glVertex3f( 0.5f,  0.18f, 0.30f);
    glVertex3f( 0.5f, -0.18f, 0.30f);

    glEnd();

    //
    // ARROW NOSE
    //

    glColor3f(
        0.86f,
        0.15f,
        0.15f
    );

    glBegin(GL_TRIANGLES);

    //
    // TOP FACE
    //

    glVertex3f(1.45f,  0.0f,  0.0f);
    glVertex3f(0.5f,   0.22f, -0.38f);
    glVertex3f(0.5f,   0.22f,  0.38f);

    //
    // BOTTOM FACE
    //

    glVertex3f(1.45f,  0.0f,  0.0f);
    glVertex3f(0.5f,  -0.22f,  0.38f);
    glVertex3f(0.5f,  -0.22f, -0.38f);

    //
    // LEFT FACE
    //

    glVertex3f(1.45f,  0.0f,  0.0f);
    glVertex3f(0.5f,   0.22f, -0.38f);
    glVertex3f(0.5f,  -0.22f, -0.38f);

    //
    // RIGHT FACE
    //

    glVertex3f(1.45f,  0.0f,  0.0f);
    glVertex3f(0.5f,   0.22f,  0.38f);
    glVertex3f(0.5f,  -0.22f,  0.38f);

    glEnd();

    //
    // CENTER LINE
    //

    glLineWidth(2.0f);

    glColor3f(
        0.55f,
        0.55f,
        0.55f
    );

    glBegin(GL_LINES);

    glVertex3f(-1.2f, 0.25f, 0.0f);
    glVertex3f( 1.45f,0.25f, 0.0f);

    glEnd();

    //
    // END TRANSFORM
    //

    glPopMatrix();

    //
    // CONTINUOUS UPDATE
    //

    update();
}