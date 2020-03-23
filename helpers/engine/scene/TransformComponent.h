#pragma once

#include "ITransform.h"

template<class T>
class TransformComponent : ITransform
{
public:
    T transform;

    glm::mat4 getLocalToWorldMatrix() const
    {
        return transform.getLocalToWorldMatrix();
    }
};
