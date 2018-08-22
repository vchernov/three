#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace three
{

struct ModelTransform final
{
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 eulerAngles = glm::vec3(0.0f);

    glm::mat4 getTransformationMatrix() const;
};

}
