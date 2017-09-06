#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace three {

OrthographicCamera::OrthographicCamera(float width, float height, float near, float far)
    :
    width(width),
    height(height),
    near(near),
    far(far) {
}

float OrthographicCamera::getWidth() const {
    return width;
}

void OrthographicCamera::setWidth(float width) {
    this->width = width;
}

float OrthographicCamera::getHeight() const {
    return height;
}

void OrthographicCamera::setHeight(float height) {
    this->height = height;
}

float OrthographicCamera::getNear() const {
    return near;
}

void OrthographicCamera::setNear(float near) {
    this->near = near;
}

float OrthographicCamera::getFar() const {
    return far;
}

void OrthographicCamera::setFar(float far) {
    this->far = far;
}

glm::mat4 OrthographicCamera::getProjectionMatrix() const {
    return glm::ortho(0.0f, width, 0.0f, height, near, far);
}

}
