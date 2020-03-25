#pragma once

#include "ITransform.h"

template<class T>
class TransformComponent : public ITransform
{
public:
    T transform;

    glm::mat4 getLocalToWorldMatrix() const override
    {
        return transform.getLocalToWorldMatrix();
    }
};
