#pragma once

#include "Camera.h"

namespace three
{

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fieldOfView, float aspect, float near, float far);

    float getFieldOfView() const;
    void setFieldOfView(float fieldOfView);

    float getAspect() const;
    void setAspect(float aspect);

    float getNear() const;
    void setNear(float near);

    float getFar() const;
    void setFar(float far);

    glm::mat4 getProjectionMatrix() const override;

private:
    float fieldOfView;
    float aspect;
    float near;
    float far;
};

}
