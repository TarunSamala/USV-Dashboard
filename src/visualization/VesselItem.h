#pragma once

#include <QQuickFramebufferObject>

class VesselItem : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(float roll READ roll WRITE setRoll NOTIFY rollChanged)
    Q_PROPERTY(float pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(float yaw READ yaw WRITE setYaw NOTIFY yawChanged)

public:
    explicit VesselItem(QQuickItem *parent = nullptr);

    Renderer *createRenderer() const override;

    float roll() const;
    float pitch() const;
    float yaw() const;

    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);

signals:
    void rollChanged();
    void pitchChanged();
    void yawChanged();

private:
    float m_roll = 0.f;
    float m_pitch = 0.f;
    float m_yaw = 0.f;
};