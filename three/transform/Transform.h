#pragma once

#include <glm/glm.hpp>

namespace three
{

class Transform final
{
public:
    void set(glm::mat4 matrix);

    glm::mat4 getLocalToWorldMatrix() const;

    void translate(glm::vec3 translation);
    void scale(glm::vec3 scale);
    void rotate(float angle, glm::vec3 axis);

    void lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

private:
    glm::mat4 matrix = glm::mat4(1.0f);
};

}
