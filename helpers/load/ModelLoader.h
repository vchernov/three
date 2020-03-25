#pragma once

#include <string>
#include <vector>

#include "../engine/scene/Scene.h"

class ModelLoader
{
public:
	static std::vector<Scene> loadModel(const std::string& fn);
};
