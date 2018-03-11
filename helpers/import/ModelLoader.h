#pragma once

#include <string>
#include <vector>

#include "../../three/mesh/Mesh.h"

#include "../engine/BoundingBox.h"

class ModelLoader {
public:
    static std::vector<three::Mesh> load(const std::string& fn, BoundingBox& bounds);
};
