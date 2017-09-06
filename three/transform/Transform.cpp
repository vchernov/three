#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace three {

glm::mat4 Transform::getTransformationMatrix() const {
    return transform;
}

void Transform::translate(glm::vec3 translation) {
    transform = glm::translate(transform, translation);
}

void Transform::scale(glm::vec3 scale) {
    transform = glm::scale(transform, scale);
}

void Transform::rotate(float angle, glm::vec3 axis) {
    transform = glm::rotate(transform, glm::radians(angle), axis);
}

void Transform::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    transform = glm::lookAt(eye, center, up);
}

}
