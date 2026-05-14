#include "VesselItem.h"

#include "VesselRenderer.h"

#include <QMouseEvent>

VesselItem::VesselItem(
    QQuickItem* parent
)
    : QQuickFramebufferObject(parent)
{
    setAcceptedMouseButtons(
        Qt::AllButtons
    );

    setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer*
VesselItem::createRenderer() const
{
    return new VesselRenderer(
        const_cast<VesselItem*>(this)
    );
}

float VesselItem::roll() const
{
    return m_roll;
}

float VesselItem::pitch() const
{
    return m_pitch;
}

float VesselItem::yaw() const
{
    return m_yaw;
}

void VesselItem::setRoll(float value)
{
    if (m_roll == value)
        return;

    m_roll = value;

    emit rollChanged();

    update();
}

void VesselItem::setPitch(float value)
{
    if (m_pitch == value)
        return;

    m_pitch = value;

    emit pitchChanged();

    update();
}

void VesselItem::setYaw(float value)
{
    if (m_yaw == value)
        return;

    m_yaw = value;

    emit yawChanged();

    update();
}

void VesselItem::mousePressEvent(
    QMouseEvent* event
)
{
    m_lastMousePos =
        event->position();
}

void VesselItem::mouseMoveEvent(
    QMouseEvent* event
)
{
    QPointF delta =
        event->position()
        - m_lastMousePos;

    cameraYaw += delta.x() * 0.5f;

    cameraPitch += delta.y() * 0.5f;

    if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;

    if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;

    m_lastMousePos =
        event->position();

    update();
}

void VesselItem::wheelEvent(
    QWheelEvent* event
)
{
    cameraDistance -=
        event->angleDelta().y()
        * 0.002f;

    if (cameraDistance < 2.0f)
        cameraDistance = 2.0f;

    if (cameraDistance > 20.0f)
        cameraDistance = 20.0f;

    update();
}