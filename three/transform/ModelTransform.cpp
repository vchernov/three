#include "ModelTransform.h"

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace three
{

glm::mat4 ModelTransform::getLocalToWorldMatrix() const
{
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::scale(matrix, scale);
    glm::mat4 rotation = glm::eulerAngleXYZ(
        glm::radians(eulerAngles.x),
        glm::radians(eulerAngles.y),
        glm::radians(eulerAngles.z));
    return matrix * rotation;
}

}
