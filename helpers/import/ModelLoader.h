#pragma once

#include <string>
#include <vector>

#include "../../three/mesh/Face.h"

#include "../engine/Model.h"
#include "../engine/Geometry.h"
#include "../engine/Vertex.h"

class ModelLoader {
public:
    using Face = three::Face<unsigned int, 3>;
    using Geometry = Geometry<VertexPositionNormal, Face>;

    static std::vector<Geometry> loadGeometry(const std::string& fn);
};
