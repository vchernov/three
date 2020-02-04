#include "SubMesh.h"

SubMesh::SubMesh(three::Mesh mesh)
    :
    mesh(std::move(mesh))
{
}
