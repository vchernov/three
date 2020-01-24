#include "ModelLoader.h"

#include "../../helpers/engine/Model.h"

#include "../../3rdparty/fx-gltf/include/fx/gltf.h"

#include <iostream>

using namespace three;

void ModelLoader::loadModel(const std::string& fn)
{
	fx::gltf::Document doc = fx::gltf::LoadFromText(fn);

	for (const auto& buffer : doc.buffers)
	{
	}

	for (const auto& mesh : doc.meshes)
	{
		for (const auto& primitive : mesh.primitives)
		{
			const auto& accessor = doc.accessors[primitive.indices];
			const auto& bufferView = doc.bufferViews[accessor.bufferView];

			IndexBuffer indexBuffer;
			indexBuffer.bind();

			const auto& buffer = doc.buffers[bufferView.buffer];
			indexBuffer.allocate((GLenum)accessor.componentType,
				4, bufferView.byteLength, &buffer.data[bufferView.byteOffset]);

			IndexBuffer::unbind();
		}
	}
}
