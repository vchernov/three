#pragma once

#include "Camera.h"

namespace three {

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float width, float height, float near, float far);

    float getWidth() const;
    void setWidth(float width);

    float getHeight() const;
    void setHeight(float height);

    float getNear() const;
    void setNear(float near);

    float getFar() const;
    void setFar(float far);

    glm::mat4 getProjectionMatrix() const override;

private:
    float width;
    float height;
    float near;
    float far;
};

}
