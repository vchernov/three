#include "ModelLoader.h"

#include <fx/gltf.h>

void ModelLoader::loadModel(const std::string& fn)
{
	fx::gltf::Document doc = fx::gltf::LoadFromText(fn);
}
