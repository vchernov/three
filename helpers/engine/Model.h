#pragma once

#include <vector>

#include "../../three/transform/ModelTransform.h"
#include "../../three/mesh/Mesh.h"

#include "BoundingBox.h"

class Model {
public:
    std::vector<three::Mesh> meshes;
    BoundingBox bounds;
    three::ModelTransform transform;

    void draw() const;
};
