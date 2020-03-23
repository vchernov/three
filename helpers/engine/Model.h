#pragma once

#include <glm/glm.hpp>

#include "../../three/mesh/Mesh.h"

#include "BoundingBox.h"
#include "Material.h"

class Model
{
public:
    Model(three::Mesh mesh);

    three::Mesh mesh;
    BoundingBox bounds;
    Material material;

    void draw(glm::mat4) const;
};
