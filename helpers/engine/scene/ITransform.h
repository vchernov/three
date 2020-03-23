#pragma once

#include <glm/glm.hpp>

class ITransform
{
public:
    virtual ~ITransform() = default;

    virtual glm::mat4 getLocalToWorldMatrix() const = 0;
};
