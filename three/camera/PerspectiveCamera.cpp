#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace three {

PerspectiveCamera::PerspectiveCamera(float fieldOfView, float aspect, float near, float far)
    :
    fieldOfView(fieldOfView),
    aspect(aspect),
    near(near),
    far(far) {
}

float PerspectiveCamera::getFieldOfView() const {
    return fieldOfView;
}

void PerspectiveCamera::setFieldOfView(float fieldOfView) {
    this->fieldOfView = fieldOfView;
}

float PerspectiveCamera::getAspect() const {
    return aspect;
}

void PerspectiveCamera::setAspect(float aspect) {
    this->aspect = aspect;
}

float PerspectiveCamera::getNear() const {
    return near;
}

void PerspectiveCamera::setNear(float near) {
    this->near = near;
}

float PerspectiveCamera::getFar() const {
    return far;
}

void PerspectiveCamera::setFar(float far) {
    this->far = far;
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fieldOfView), aspect, near, far);
}

}
