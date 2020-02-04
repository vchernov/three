#pragma once

#include <string>
#include <vector>

#include "../../three/mesh/Face.h"

#include "../engine/Geometry.h"
#include "../engine/Model.h"
#include "../engine/Vertex.h"
#include "../engine/Material.h"

#include "../image/ImageUtils.h"

class ModelImporter
{
public:
    using IndexedTriangle = three::Face<unsigned int, 3>;
    using ModelGeometry = Geometry<VertexPositionNormalTexture, IndexedTriangle>;

    struct ModelData
    {
        ModelGeometry geo;
        ImageRGB diffuseMap;

        ModelData(ModelGeometry geo, ImageRGB diffuseMap);
    };

    static std::vector<ModelData> loadGeometry(const std::string& fn);
};
