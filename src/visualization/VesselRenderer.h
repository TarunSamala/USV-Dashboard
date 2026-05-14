#pragma once

#include <QQuickFramebufferObject>

#include <QOpenGLFunctions>

class VesselItem;

class VesselRenderer
    : public QQuickFramebufferObject::Renderer,
      protected QOpenGLFunctions
{
public:

    explicit VesselRenderer(
        VesselItem* item
    );

    void render() override;

    void synchronize(
        QQuickFramebufferObject *item
    ) override;

private:

    float m_roll = 0.f;

    float m_pitch = 0.f;

    float m_yaw = 0.f;
};