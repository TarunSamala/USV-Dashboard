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

    //
    // QQuickFramebufferObject
    //

    void render() override;

    void synchronize(
        QQuickFramebufferObject* item
    ) override;

private:

    //
    // IMU ORIENTATION
    //

    float m_roll = 0.0f;

    float m_pitch = 0.0f;

    float m_yaw = 0.0f;

    //
    // CAMERA
    //

    float m_cameraYaw = 45.0f;

    float m_cameraPitch = 25.0f;

    float m_cameraDistance = 6.0f;
};