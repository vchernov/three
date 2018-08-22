#pragma once

#include <vector>

#include <glm/glm.hpp>

struct BoundingBox final
{
    glm::vec3 pointFrontBottomLeft;
    glm::vec3 pointBackTopRight;

    BoundingBox();

    void encapsulate(float x, float y, float z);
    void encapsulate(const glm::vec3& point);
    void encapsulate(const BoundingBox& other);

    template<typename VertexType>
    static BoundingBox calculate(const std::vector<VertexType>& vertices)
    {
        BoundingBox bounds;
        for (const auto& vertex : vertices)
        {
            bounds.encapsulate(vertex.position);
        }
        return bounds;
    }

    glm::vec3 getSize() const;
    glm::vec3 getCenter() const;
};
