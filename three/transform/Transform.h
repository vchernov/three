#pragma once

#include <glm/glm.hpp>

namespace three {

class Transform {
public:
    virtual ~Transform() = default;

    glm::mat4 getTransformationMatrix() const;

    void translate(glm::vec3 translation);
    void scale(glm::vec3 scale);
    void rotate(float angle, glm::vec3 axis);

    void lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

private:
    glm::mat4 transform = glm::mat4(1.0f);
};

}
