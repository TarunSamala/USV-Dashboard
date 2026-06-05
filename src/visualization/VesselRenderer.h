#pragma once

#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>

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
        QQuickFramebufferObject* item
    ) override;

private:

    float m_roll  = 0.0f;
    float m_pitch = 0.0f;
    float m_yaw   = 0.0f;

    void drawGrid();
    void drawWorldAxes();
    void drawCubeBounds();
    void drawVessel();
    void drawAxisIndicator(
        int viewportWidth,
        int viewportHeight
    );
};