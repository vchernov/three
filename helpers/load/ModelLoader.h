#pragma once

#include <string>
#include <vector>

#include "../engine/scene/Scene.h"

class ModelLoader
{
public:
    static void loadScene(const std::string& fn, std::vector<Scene>& scenes);
};
