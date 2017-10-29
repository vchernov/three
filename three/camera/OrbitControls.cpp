#include "OrbitControls.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/polar_coordinates.hpp>

namespace three {

glm::mat4 OrbitControls::getViewMatrix() const {
    glm::vec3 offset = glm::euclidean(rotation) * radius;

    glm::vec3 forward = -offset;
    glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 up = glm::cross(right, forward);

    glm::vec3 eye = center + offset;

    return glm::lookAt(eye, center, up);
}

glm::vec3 OrbitControls::getEyePosition() const {
    return center + glm::euclidean(rotation) * radius;
}

void OrbitControls::yaw(float angle) {
    rotation.x += glm::radians(angle) * rotationSpeed;

    const auto rotMin = -glm::half_pi<float>() + glm::epsilon<float>();
    const auto rotMax = glm::half_pi<float>() - glm::epsilon<float>();

    rotation.x = glm::clamp(rotation.x, rotMin, rotMax);
}

void OrbitControls::pitch(float angle) {
    rotation.y -= glm::radians(angle) * rotationSpeed;
}

void OrbitControls::zoom(float amount) {
    radius -= amount * zoomSpeed;
    if (radius < minRadius) {
        radius = minRadius;
    }
}

void OrbitControls::move(float x, float y) {
    glm::vec3 offset = glm::euclidean(rotation) * radius;

    glm::vec3 forward = -offset;
    glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 up = glm::cross(right, forward);

    center += glm::normalize(right) * x * moveSpeed;
    center += glm::normalize(up) * y * moveSpeed;
}

void OrbitControls::setRotationSpeed(float rotationSpeed) {
    this->rotationSpeed = rotationSpeed;
}

void OrbitControls::setZoomSpeed(float zoomSpeed) {
    this->zoomSpeed = zoomSpeed;
}

void OrbitControls::setMoveSpeed(float moveSpeed) {
    this->moveSpeed = moveSpeed;
}

void OrbitControls::setRadius(float radius) {
    this->radius = radius;
}

void OrbitControls::setMinRadius(float minRadius) {
    this->minRadius = minRadius;
}

}
