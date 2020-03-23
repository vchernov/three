#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../Model.h"
#include "ITransform.h"

struct Node
{
    std::vector<Node> children;

    std::vector<Model> models;
    std::vector<std::unique_ptr<ITransform>> transforms;

    void draw(glm::mat4 matrix) const;
};
