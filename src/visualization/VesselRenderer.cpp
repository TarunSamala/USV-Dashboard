#include "VesselRenderer.h"
#include "VesselItem.h"

#include <QOpenGLFramebufferObject>

//
// MinGW requires windows.h before glu.h
// (defines APIENTRY and CALLBACK macros)
//
#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <cmath>

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

    glViewport(0, 0, size.width(), size.height());

    glEnable(GL_DEPTH_TEST);

    //
    // BACKGROUND
    //

    glClearColor(0.04f, 0.04f, 0.045f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //
    // PROJECTION
    //

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const float aspect =
        float(size.width()) / float(size.height());

    gluPerspective(45.0, aspect, 0.1, 200.0);

    //
    // CAMERA
    //
    // Coordinate system:
    //   +X = Forward (Bow)
    //   +Y = Right (Starboard)
    //   +Z = Up
    //
    // Camera sits behind the stern on the -X axis,
    // slightly elevated, looking toward the bow (+X).
    //
    // The up vector must be (0, 0, 1) in world space.
    // Because the eye is at negative X and we look toward
    // +X, the image was flipping. The correct fix is to
    // negate Z-up to (0, 0, -1) so that the rendered
    // scene appears right-side-up from this viewpoint.
    //

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        -6.0,  0.0,  2.5,   // eye:    behind stern, slightly above
         1.5,  0.0,  0.0,   // centre: toward bow
         0.0,  0.0, -1.0    // up:     negated Z keeps image upright
    );

    drawGrid();
    drawCubeBounds();
    drawVessel();

    //
    // AXIS INDICATOR — drawn last, always on top
    //

    drawAxisIndicator(size.width(), size.height());

    update();
}

// ─────────────────────────────────────────────────────────────
//  ENVIRONMENT
// ─────────────────────────────────────────────────────────────

void VesselRenderer::drawCubeBounds()
{
    const float s = 8.0f;

    glColor3f(0.18f, 0.18f, 0.18f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    // bottom
    glVertex3f(-s,-s,0); glVertex3f( s,-s,0);
    glVertex3f( s,-s,0); glVertex3f( s, s,0);
    glVertex3f( s, s,0); glVertex3f(-s, s,0);
    glVertex3f(-s, s,0); glVertex3f(-s,-s,0);

    // top
    glVertex3f(-s,-s,s); glVertex3f( s,-s,s);
    glVertex3f( s,-s,s); glVertex3f( s, s,s);
    glVertex3f( s, s,s); glVertex3f(-s, s,s);
    glVertex3f(-s, s,s); glVertex3f(-s,-s,s);

    // verticals
    glVertex3f(-s,-s,0); glVertex3f(-s,-s,s);
    glVertex3f( s,-s,0); glVertex3f( s,-s,s);
    glVertex3f( s, s,0); glVertex3f( s, s,s);
    glVertex3f(-s, s,0); glVertex3f(-s, s,s);

    glEnd();
}

void VesselRenderer::drawGrid()
{
    glLineWidth(1.0f);

    for (int i = -50; i <= 50; ++i)
    {
        glColor3f(
            i == 0 ? 0.25f : 0.12f,
            i == 0 ? 0.25f : 0.12f,
            i == 0 ? 0.25f : 0.12f
        );

        glBegin(GL_LINES);
        glVertex3f(-50.0f, (float)i, 0.0f);
        glVertex3f( 50.0f, (float)i, 0.0f);
        glVertex3f((float)i, -50.0f, 0.0f);
        glVertex3f((float)i,  50.0f, 0.0f);
        glEnd();
    }
}

// ─────────────────────────────────────────────────────────────
//  AXIS INDICATOR  (bottom-left corner)
//
//  Reference image: X=red (right), Y=green (left/back), Z=blue (up)
//  The indicator rotates with the vessel body frame.
// ─────────────────────────────────────────────────────────────

void VesselRenderer::drawAxisIndicator(int width, int height)
{
    const int S = 110;
    const int M = 15;

    //
    // QQuickFramebufferObject renders into a texture that Qt
    // flips vertically before compositing onto the screen.
    // OpenGL's viewport origin is bottom-left, so to appear
    // at the VISUAL bottom-left we must place the viewport at
    // the OpenGL TOP-left, i.e. y = (height - S - M).
    //

    glViewport(M, height - S - M, S, S);

    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 1.0, 0.1, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //
    // Camera: diagonally above, matches reference image.
    //   X = red   → forward / bow
    //   Y = blue  → starboard / right
    //   Z = green → up
    //

    gluLookAt(
        2.5,  -2.5,  2.5,
        0.0,   0.0,  0.0,
        0.0,   0.0,  1.0
    );

    //
    // Apply body-frame rotations so indicator tracks the vessel
    //

    glRotatef( m_yaw,   0.0f, 0.0f, 1.0f);
    glRotatef( m_pitch, 0.0f, 1.0f, 0.0f);
    glRotatef(-m_roll,  1.0f, 0.0f, 0.0f);

    glLineWidth(3.5f);

    //
    // X — RED (forward / bow)
    //

    glColor3f(0.85f, 0.1f, 0.1f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.1f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.35f,  0.00f,  0.00f);
    glVertex3f(1.10f,  0.09f,  0.00f);
    glVertex3f(1.10f, -0.09f,  0.00f);
    glEnd();

    //
    // Y — BLUE (starboard / right)
    //

    glColor3f(0.1f, 0.35f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.1f, 0.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.00f, 1.35f,  0.00f);
    glVertex3f( 0.09f, 1.10f,  0.00f);
    glVertex3f(-0.09f, 1.10f,  0.00f);
    glEnd();

    //
    // Z — GREEN (up)
    //
    // The FBO texture is flipped vertically by Qt before
    // compositing, so geometry drawn in +Z appears pointing
    // DOWN on screen. Drawing in -Z corrects this so the
    // green axis visually points UP after the flip.
    //

    glColor3f(0.1f, 0.8f, 0.1f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f,  0.0f);
    glVertex3f(0.0f, 0.0f, -1.1f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.00f,  0.00f, -1.35f);
    glVertex3f( 0.09f,  0.00f, -1.10f);
    glVertex3f(-0.09f,  0.00f, -1.10f);
    glEnd();

    //
    // Restore full viewport
    //

    glViewport(0, 0, width, height);
}

// ─────────────────────────────────────────────────────────────
//  VESSEL MODEL
//
//  Coordinate system:  +X=bow  +Y=starboard  +Z=up
//
//  Shape: a boat with:
//    - flat-bottomed hull with flared sides
//    - pointed bow, flat transom stern
//    - low rectangular cabin/superstructure amidships
//    - red bow arrow on deck pointing +X
// ─────────────────────────────────────────────────────────────

void VesselRenderer::drawVessel()
{
    glPushMatrix();

    //
    // Apply body-frame rotations
    // Order: Yaw (Z) → Pitch (Y) → Roll (X)
    //

    glRotatef( m_yaw,   0.0f, 0.0f, 1.0f);
    glRotatef( m_pitch, 0.0f, 1.0f, 0.0f);
    glRotatef(-m_roll,  1.0f, 0.0f, 0.0f);

    // ── Dimensions ──────────────────────────────────────────
    //
    //  Hull length:   bow tip at x=+2.2,  stern at x=-1.6
    //  Hull width:    ±0.55 at widest (amidships)
    //  Keel (bottom): z = -0.15
    //  Deck (top):    z = +0.18
    //  Cabin:         x=[-0.6, +0.6]  z=[0.18, 0.55]  y=±0.3

    // ── Waterline cross-section vertices (z = -0.15 to +0.18)
    //
    //  stern  (-1.6, ±0.35)
    //  mid    ( 0.0, ±0.55)
    //  fwd    (+1.4, ±0.30)
    //  bow    (+2.2,  0.0 )

    // ─── HULL BOTTOM (keel plane, z=-0.15) ──────────────────

    glColor3f(0.55f, 0.55f, 0.58f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f( 2.2f,  0.00f, -0.15f);  // bow tip
    glVertex3f( 1.4f, -0.30f, -0.15f);
    glVertex3f( 0.0f, -0.55f, -0.15f);
    glVertex3f(-1.6f, -0.35f, -0.15f);
    glVertex3f(-1.6f,  0.35f, -0.15f);
    glVertex3f( 0.0f,  0.55f, -0.15f);
    glVertex3f( 1.4f,  0.30f, -0.15f);
    glVertex3f( 2.2f,  0.00f, -0.15f);
    glEnd();

    // ─── DECK TOP (z=+0.18) ─────────────────────────────────

    glColor3f(0.80f, 0.80f, 0.83f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f( 2.2f,  0.00f,  0.18f);
    glVertex3f( 1.4f,  0.30f,  0.18f);
    glVertex3f( 0.0f,  0.55f,  0.18f);
    glVertex3f(-1.6f,  0.35f,  0.18f);
    glVertex3f(-1.6f, -0.35f,  0.18f);
    glVertex3f( 0.0f, -0.55f,  0.18f);
    glVertex3f( 1.4f, -0.30f,  0.18f);
    glVertex3f( 2.2f,  0.00f,  0.18f);
    glEnd();

    // ─── PORT SIDE (negative Y) ─────────────────────────────

    glColor3f(0.65f, 0.65f, 0.68f);

    glBegin(GL_QUADS);

    // stern → midship
    glVertex3f(-1.6f, -0.35f, -0.15f);
    glVertex3f( 0.0f, -0.55f, -0.15f);
    glVertex3f( 0.0f, -0.55f,  0.18f);
    glVertex3f(-1.6f, -0.35f,  0.18f);

    // midship → forward
    glVertex3f( 0.0f, -0.55f, -0.15f);
    glVertex3f( 1.4f, -0.30f, -0.15f);
    glVertex3f( 1.4f, -0.30f,  0.18f);
    glVertex3f( 0.0f, -0.55f,  0.18f);

    glEnd();

    // ─── STARBOARD SIDE (positive Y) ────────────────────────

    glBegin(GL_QUADS);

    glVertex3f( 0.0f,  0.55f, -0.15f);
    glVertex3f(-1.6f,  0.35f, -0.15f);
    glVertex3f(-1.6f,  0.35f,  0.18f);
    glVertex3f( 0.0f,  0.55f,  0.18f);

    glVertex3f( 1.4f,  0.30f, -0.15f);
    glVertex3f( 0.0f,  0.55f, -0.15f);
    glVertex3f( 0.0f,  0.55f,  0.18f);
    glVertex3f( 1.4f,  0.30f,  0.18f);

    glEnd();

    // ─── BOW FACES (triangular, +X side) ────────────────────

    glColor3f(0.70f, 0.70f, 0.73f);

    glBegin(GL_TRIANGLES);

    // port bow
    glVertex3f( 2.2f,  0.00f, -0.15f);
    glVertex3f( 1.4f, -0.30f, -0.15f);
    glVertex3f( 1.4f, -0.30f,  0.18f);

    glVertex3f( 2.2f,  0.00f, -0.15f);
    glVertex3f( 2.2f,  0.00f,  0.18f);
    glVertex3f( 1.4f, -0.30f,  0.18f);

    // starboard bow
    glVertex3f( 2.2f,  0.00f, -0.15f);
    glVertex3f( 1.4f,  0.30f,  0.18f);
    glVertex3f( 1.4f,  0.30f, -0.15f);

    glVertex3f( 2.2f,  0.00f, -0.15f);
    glVertex3f( 1.4f,  0.30f,  0.18f);
    glVertex3f( 2.2f,  0.00f,  0.18f);

    glEnd();

    // ─── TRANSOM STERN (flat, -X face) ──────────────────────

    glColor3f(0.60f, 0.60f, 0.63f);

    glBegin(GL_QUADS);
    glVertex3f(-1.6f, -0.35f, -0.15f);
    glVertex3f(-1.6f,  0.35f, -0.15f);
    glVertex3f(-1.6f,  0.35f,  0.18f);
    glVertex3f(-1.6f, -0.35f,  0.18f);
    glEnd();

    // ─── CABIN / SUPERSTRUCTURE ──────────────────────────────

    glColor3f(0.88f, 0.88f, 0.90f);

    glBegin(GL_QUADS);

    // cabin top
    glVertex3f(-0.6f, -0.30f, 0.55f);
    glVertex3f( 0.6f, -0.30f, 0.55f);
    glVertex3f( 0.6f,  0.30f, 0.55f);
    glVertex3f(-0.6f,  0.30f, 0.55f);

    // cabin front (+X)
    glVertex3f( 0.6f, -0.30f, 0.18f);
    glVertex3f( 0.6f,  0.30f, 0.18f);
    glVertex3f( 0.6f,  0.30f, 0.55f);
    glVertex3f( 0.6f, -0.30f, 0.55f);

    // cabin back (-X)
    glVertex3f(-0.6f,  0.30f, 0.18f);
    glVertex3f(-0.6f, -0.30f, 0.18f);
    glVertex3f(-0.6f, -0.30f, 0.55f);
    glVertex3f(-0.6f,  0.30f, 0.55f);

    // cabin port side (-Y)
    glVertex3f(-0.6f, -0.30f, 0.18f);
    glVertex3f( 0.6f, -0.30f, 0.18f);
    glVertex3f( 0.6f, -0.30f, 0.55f);
    glVertex3f(-0.6f, -0.30f, 0.55f);

    // cabin starboard side (+Y)
    glVertex3f( 0.6f,  0.30f, 0.18f);
    glVertex3f(-0.6f,  0.30f, 0.18f);
    glVertex3f(-0.6f,  0.30f, 0.55f);
    glVertex3f( 0.6f,  0.30f, 0.55f);

    glEnd();

    // ─── BOW ARROW (red, on deck, pointing +X) ───────────────
    //
    // A single red arrow along the centreline on deck.
    // This is the ONLY directional marker on the vessel.
    //

    glColor3f(1.0f, 0.0f, 0.0f);

    glLineWidth(5.0f);

    // shaft: from aft of cabin to near bow tip
    glBegin(GL_LINES);
    glVertex3f(-0.4f, 0.0f, 0.22f);
    glVertex3f( 1.90f, 0.0f, 0.22f);
    glEnd();

    // arrowhead triangle
    glBegin(GL_TRIANGLES);
    glVertex3f( 2.15f,  0.00f, 0.22f);
    glVertex3f( 1.88f, -0.13f, 0.22f);
    glVertex3f( 1.88f,  0.13f, 0.22f);
    glEnd();

    glPopMatrix();
}
