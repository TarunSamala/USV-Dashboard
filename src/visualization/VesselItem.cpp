#include "VesselItem.h"

#include "VesselRenderer.h"

VesselItem::VesselItem(
    QQuickItem *parent
)
    : QQuickFramebufferObject(parent)
{
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

void VesselItem::setRoll(
    float value
)
{
    if (m_roll == value)
        return;

    m_roll = value;

    emit rollChanged();

    update();
}

void VesselItem::setPitch(
    float value
)
{
    if (m_pitch == value)
        return;

    m_pitch = value;

    emit pitchChanged();

    update();
}

void VesselItem::setYaw(
    float value
)
{
    if (m_yaw == value)
        return;

    m_yaw = value;

    emit yawChanged();

    update();
}