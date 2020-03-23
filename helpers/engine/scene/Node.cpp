#include "Node.h"

void Node::draw(glm::mat4 matrix) const
{
    for (const auto& transform : transforms)
        matrix *= transform->getLocalToWorldMatrix();

    for (const auto& model : models)
        model.draw(matrix);

    for (const auto& child : children)
        child.draw(matrix);
}
