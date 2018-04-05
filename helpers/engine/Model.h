#pragma once

#include <vector>

#include "../../three/transform/ModelTransform.h"

#include "SubMesh.h"

struct Model final {
    std::vector<SubMesh> meshes;
    three::ModelTransform transform;

    void draw() const;
};
