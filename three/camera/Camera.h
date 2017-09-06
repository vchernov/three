#pragma once

#include <glm/glm.hpp>

namespace three {

class Camera {
public:
    virtual ~Camera() = default;

    virtual glm::mat4 getProjectionMatrix() const = 0;
};

}
