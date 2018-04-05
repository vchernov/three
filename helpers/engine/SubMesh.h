#pragma once

#include "../../three/mesh/Mesh.h"

#include "BoundingBox.h"

class SubMesh {
public:
    SubMesh(three::Mesh mesh, BoundingBox bounds);
    virtual ~SubMesh() = default;

    SubMesh(SubMesh&&) noexcept = default;
    SubMesh& operator=(SubMesh&&) = default;

    const three::Mesh& getMesh() const;
    const BoundingBox& getBounds() const;

private:
    three::Mesh mesh;
    BoundingBox bounds;
};
