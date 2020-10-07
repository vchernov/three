#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace three
{

void Transform::set(glm::mat4 matrix)
{
    this->matrix = matrix;
}

glm::mat4 Transform::getLocalToWorldMatrix() const
{
    return matrix;
}

void Transform::translate(glm::vec3 translation)
{
    matrix = glm::translate(matrix, translation);
}

void Transform::scale(glm::vec3 scale)
{
    matrix = glm::scale(matrix, scale);
}

void Transform::rotate(float angle, glm::vec3 axis)
{
    matrix = glm::rotate(matrix, glm::radians(angle), axis);
}

void Transform::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    matrix = glm::lookAt(eye, center, up);
}

}
