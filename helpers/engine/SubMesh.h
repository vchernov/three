#pragma once

#include "../../three/mesh/Mesh.h"

#include "BoundingBox.h"
#include "Material.h"

struct SubMesh final
{
    three::Mesh mesh;
    BoundingBox bounds;
    Material material;

    SubMesh(three::Mesh mesh);
};
