#include "SubMesh.h"

SubMesh::SubMesh(three::Mesh mesh, BoundingBox bounds)
    :
    mesh(std::move(mesh)),
    bounds(bounds) {
}

const three::Mesh& SubMesh::getMesh() const {
    return mesh;
}

const BoundingBox& SubMesh::getBounds() const {
    return bounds;
}
