#include "ModelLoader.h"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include "gltf.h"
#include "../../helpers/engine/Model.h"

using namespace three;
using json = nlohmann::json;

void ModelLoader::loadModel(const std::string& fn)
{
    std::ifstream f(fn);
    if (!f.is_open())
        return;

    json j = json::parse(f);
    auto doc = j.get<gltf::Document>();
}
