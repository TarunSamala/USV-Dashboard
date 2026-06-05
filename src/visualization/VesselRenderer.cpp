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
    // CAMERA: BEHIND VESSEL (STERN VIEW)
    //
    // Coordinate system:
    //   +X = Forward (Bow)
    //   +Y = Right
    //   +Z = Up
    //
    // Camera is placed at -X (behind stern), slightly
    // elevated, looking toward +X (bow).
    // Up vector is +Z.
    //

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(
        -6.0,   // eye X  (behind stern)
         0.0,   // eye Y  (centred laterally)
         2.5,   // eye Z  (slightly above)

         1.5,   // centre X  (bow side)
         0.0,   // centre Y
         0.0,   // centre Z

         0.0,   // up X
         0.0,   // up Y
         1.0    // up Z  (+Z is up)
    );

    drawGrid();

    drawCubeBounds();

    drawWorldAxes();

    drawVessel();

    //
    // AXIS INDICATOR — drawn last, no depth occlusion
    //

    drawAxisIndicator(
        size.width(),
        size.height()
    );

    update();
}

void VesselRenderer::drawCubeBounds()
{
    const float s = 8.0f;

    glColor3f(0.18f,0.18f,0.18f);

    glLineWidth(1.0f);

    glBegin(GL_LINES);

    // bottom square

    glVertex3f(-s,-s,0); glVertex3f(s,-s,0);
    glVertex3f(s,-s,0);  glVertex3f(s,s,0);
    glVertex3f(s,s,0);   glVertex3f(-s,s,0);
    glVertex3f(-s,s,0);  glVertex3f(-s,-s,0);

    // top square

    glVertex3f(-s,-s,s);
    glVertex3f(s,-s,s);

    glVertex3f(s,-s,s);
    glVertex3f(s,s,s);

    glVertex3f(s,s,s);
    glVertex3f(-s,s,s);

    glVertex3f(-s,s,s);
    glVertex3f(-s,-s,s);

    // verticals

    glVertex3f(-s,-s,0);
    glVertex3f(-s,-s,s);

    glVertex3f(s,-s,0);
    glVertex3f(s,-s,s);

    glVertex3f(s,s,0);
    glVertex3f(s,s,s);

    glVertex3f(-s,s,0);
    glVertex3f(-s,s,s);

    glEnd();
}

void VesselRenderer::drawGrid()
{
    glLineWidth(1.0f);

    for (int i = -50; i <= 50; ++i)
    {
        if (i == 0)
            glColor3f(0.25f, 0.25f, 0.25f);
        else
            glColor3f(0.12f, 0.12f, 0.12f);

        glBegin(GL_LINES);

        // Z = 0 plane

        glVertex3f(-50.0f, (float)i, 0.0f);
        glVertex3f( 50.0f, (float)i, 0.0f);

        glVertex3f((float)i, -50.0f, 0.0f);
        glVertex3f((float)i,  50.0f, 0.0f);

        glEnd();
    }
}

void VesselRenderer::drawWorldAxes()
{
    glLineWidth(3.0f);

    glBegin(GL_LINES);

    // X RED

    glColor3f(1.0f,0.0f,0.0f);

    glVertex3f(0,0,0);
    glVertex3f(3,0,0);

    // Y BLUE

    glColor3f(0.0f,0.35f,1.0f);

    glVertex3f(0,0,0);
    glVertex3f(0,3,0);

    // Z GREEN

    glColor3f(0.0f,1.0f,0.0f);

    glVertex3f(0,0,0);
    glVertex3f(0,0,3);

    glEnd();
}

void VesselRenderer::drawAxisIndicator(
    int width,
    int height
)
{
    //
    // AXIS INDICATOR — bottom-left corner
    //
    // Rendered after scene, in its own viewport.
    // Depth buffer cleared so it always draws on top.
    //
    // The indicator rotates with the vessel body frame
    // so the user always sees where the vessel axes are.
    //
    // Camera placed along -X, looking toward origin,
    // with +Z as up — consistent with main scene.
    //

    const int indicatorSize = 120;
    const int margin = 15;

    glViewport(
        margin,
        margin,
        indicatorSize,
        indicatorSize
    );

    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(
        35.0,
        1.0,
        0.1,
        20.0
    );

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //
    // Camera behind (-X), slightly above, +Z up
    // Matches the main scene orientation
    //

    gluLookAt(
         0.0,  0.0, 4.0,   // eye  — along +Z axis
         0.0,  0.0, 0.0,   // centre
         0.0,  1.0, 0.0    // up — +Y so Z axis goes "up" in indicator
    );

    //
    // Apply same body rotations as the vessel
    //
    // Order: Yaw (Z) → Pitch (Y) → Roll (X)
    //

    glRotatef( m_yaw,   0.0f, 0.0f, 1.0f);
    glRotatef( m_pitch, 0.0f, 1.0f, 0.0f);
    glRotatef(-m_roll,  1.0f, 0.0f, 0.0f);

    glLineWidth(4.0f);

    glBegin(GL_LINES);

    // X axis — RED (bow, forward)

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.2f, 0.0f, 0.0f);

    // Y axis — BLUE (starboard, right)

    glColor3f(0.0f, 0.3f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.2f, 0.0f);

    // Z axis — GREEN (up)

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.2f);

    glEnd();

    //
    // Arrowhead tips — small triangles at end of each axis
    //

    // X arrowhead

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glVertex3f(1.40f,  0.00f,  0.00f);
    glVertex3f(1.20f,  0.08f,  0.00f);
    glVertex3f(1.20f, -0.08f,  0.00f);
    glEnd();

    // Y arrowhead

    glColor3f(0.0f, 0.3f, 1.0f);

    glBegin(GL_TRIANGLES);
    glVertex3f( 0.00f, 1.40f,  0.00f);
    glVertex3f( 0.08f, 1.20f,  0.00f);
    glVertex3f(-0.08f, 1.20f,  0.00f);
    glEnd();

    // Z arrowhead

    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glVertex3f( 0.00f,  0.00f, 1.40f);
    glVertex3f( 0.08f,  0.00f, 1.20f);
    glVertex3f(-0.08f,  0.00f, 1.20f);
    glEnd();

    //
    // Restore full viewport
    //

    glViewport(
        0,
        0,
        width,
        height
    );
}

void VesselRenderer::drawVessel()
{
    glPushMatrix();

    //
    // BODY FRAME
    //
    // X = FORWARD (BOW)
    // Y = RIGHT (STARBOARD)
    // Z = UP
    //
    // Rotation order: Yaw (Z) → Pitch (Y) → Roll (X)
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
    // MAIN HULL — grey/white
    //

    glColor3f(
        0.84f,
        0.84f,
        0.87f
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

    // LEFT SIDE

    glVertex3f(-1.00f,-0.35f,-0.10f);
    glVertex3f( 1.20f,-0.35f,-0.10f);
    glVertex3f( 1.20f,-0.35f, 0.10f);
    glVertex3f(-1.00f,-0.35f, 0.10f);

    // RIGHT SIDE

    glVertex3f(-1.00f, 0.35f,-0.10f);
    glVertex3f( 1.20f, 0.35f,-0.10f);
    glVertex3f( 1.20f, 0.35f, 0.10f);
    glVertex3f(-1.00f, 0.35f, 0.10f);

    // STERN (back face, -X side)

    glVertex3f(-1.00f,-0.35f,-0.10f);
    glVertex3f(-1.00f, 0.35f,-0.10f);
    glVertex3f(-1.00f, 0.35f, 0.10f);
    glVertex3f(-1.00f,-0.35f, 0.10f);

    glEnd();

    //
    // BOW — tapered nose (+X side)
    //

    glColor3f(
        0.72f,
        0.72f,
        0.75f
    );

    glBegin(GL_TRIANGLES);

    glVertex3f(1.80f,0.0f,0.0f);
    glVertex3f(1.20f,-0.35f,0.10f);
    glVertex3f(1.20f, 0.35f,0.10f);

    glVertex3f(1.80f,0.0f,0.0f);
    glVertex3f(1.20f,-0.35f,-0.10f);
    glVertex3f(1.20f, 0.35f,-0.10f);

    glVertex3f(1.80f,0.0f,0.0f);
    glVertex3f(1.20f,-0.35f,-0.10f);
    glVertex3f(1.20f,-0.35f, 0.10f);

    glVertex3f(1.80f,0.0f,0.0f);
    glVertex3f(1.20f, 0.35f,-0.10f);
    glVertex3f(1.20f, 0.35f, 0.10f);

    glEnd();

    //
    // BOW ARROW — red, pointing +X on top of hull
    //

    glColor3f(
        1.0f,
        0.0f,
        0.0f
    );

    glLineWidth(5.0f);

    glBegin(GL_LINES);

    glVertex3f(-0.8f, 0.0f, 0.16f);
    glVertex3f( 1.75f,0.0f, 0.16f);

    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex3f( 1.95f,  0.0f,  0.16f);
    glVertex3f( 1.70f, -0.10f, 0.16f);
    glVertex3f( 1.70f,  0.10f, 0.16f);

    glEnd();

    glPopMatrix();
}
