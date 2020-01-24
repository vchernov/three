#pragma once

#include <string>
#include <vector>

#include "../../three/mesh/Face.h"

#include "../engine/Model.h"
#include "../engine/Geometry.h"
#include "../engine/Vertex.h"

class ModelImporter
{
public:
    using IndexedTriangle = three::Face<unsigned int, 3>;
    using ModelGeometry = Geometry<VertexPositionNormal, IndexedTriangle>;

    static std::vector<ModelGeometry> loadGeometry(const std::string& fn);
};
