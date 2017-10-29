#pragma once

#include <glm/glm.hpp>

namespace three {

class OrbitControls {
public:
    virtual ~OrbitControls() = default;

    glm::mat4 getViewMatrix() const;
    glm::vec3 getEyePosition() const;

    void yaw(float angle);
    void pitch(float angle);
    void zoom(float amount);

    void move(float x, float y);

    void setRotationSpeed(float rotationSpeed);
    void setZoomSpeed(float zoomSpeed);
    void setMoveSpeed(float moveSpeed);

    void setRadius(float radius);
    void setMinRadius(float minRadius);

private:
    float rotationSpeed = 1.0f;
    float zoomSpeed = 1.0f;
    float moveSpeed = 0.01f;
    float minRadius = 1.0f;

    glm::vec3 center = glm::vec3(0.0f);
    glm::vec2 rotation = glm::vec2(0.0f);
    float radius = minRadius;
};

}
