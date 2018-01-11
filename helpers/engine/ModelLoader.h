#pragma once

#include <string>
#include <vector>

#include "../../three/mesh/Mesh.h"

#include "IAttributeLocationBindings.h"
#include "BoundingBox.h"

class ModelLoader {
public:
    static std::vector<three::Mesh> load(const std::string& fn, const IAttributeLocationBindings* locationBindings, BoundingBox& bounds);
};
