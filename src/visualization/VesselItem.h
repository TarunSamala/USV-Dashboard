#pragma once

#include <QQuickFramebufferObject>

class VesselRenderer;

class VesselItem
    : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(
        float roll
        READ roll
        WRITE setRoll
        NOTIFY rollChanged
    )

    Q_PROPERTY(
        float pitch
        READ pitch
        WRITE setPitch
        NOTIFY pitchChanged
    )

    Q_PROPERTY(
        float yaw
        READ yaw
        WRITE setYaw
        NOTIFY yawChanged
    )

public:

    explicit VesselItem(
        QQuickItem* parent = nullptr
    );

    Renderer* createRenderer() const override;

    //
    // IMU
    //

    float roll() const;
    float pitch() const;
    float yaw() const;

    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);

    //
    // CAMERA
    //

    float cameraYaw = 45.0f;

    float cameraPitch = 25.0f;

    float cameraDistance = 6.0f;

signals:

    void rollChanged();

    void pitchChanged();

    void yawChanged();

protected:

    void mousePressEvent(
        QMouseEvent* event
    ) override;

    void mouseMoveEvent(
        QMouseEvent* event
    ) override;

    void wheelEvent(
        QWheelEvent* event
    ) override;

private:

    QPointF m_lastMousePos;

    float m_roll = 0.0f;

    float m_pitch = 0.0f;

    float m_yaw = 0.0f;
};