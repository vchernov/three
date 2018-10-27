#include "ModelLoader.h"

#include "../../3rdparty/fx-gltf/include/fx/gltf.h"

void ModelLoader::loadModel(const std::string& fn)
{
	fx::gltf::Document doc = fx::gltf::LoadFromText(fn);
}
