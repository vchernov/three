#include "ModelLoader.h"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include <glm/glm.hpp>

#include "gltf.h"

#include "../../helpers/engine/Model.h"
#include "../../helpers/engine/fs/ChangeDir.h"
#include "../../helpers/engine/fs/FileNotFoundException.h"
#include "../../helpers/engine/fs/FileSystem.h"

#include "../../helpers/image/ImageUtils.h"

using namespace three;
using json = nlohmann::json;

struct SceneData
{
    gltf::Document document;
    std::vector<char*> buffers;
    std::vector<ImageRGB> images;
};

void traverse(const gltf::Node& node, glm::mat4& matrix, const SceneData& sceneData)
{
    for (int nodeIndex : node.children)
    {
        const gltf::Node& child = sceneData.document.nodes[nodeIndex];
        traverse(child, matrix, sceneData);
    }
}

void ModelLoader::loadModel(const std::string& fn)
{
    std::ifstream gltfFile(fn);
    if (!gltfFile.is_open())
        throw FileNotFoundException(fn);

    json j = json::parse(gltfFile);
    gltfFile.close();

    auto doc = j.get<gltf::Document>();

    ChangeDir cd{FileSystem::getFilePath(fn)};

    std::vector<char*> buffers;

    for (const auto& buffer : doc.buffers)
    {
        std::fstream file(buffer.uri, std::ios::in | std::ios::binary);
        if (!file.is_open())
            throw FileNotFoundException(buffer.uri);

        char* bytes = new char[buffer.byteLength];
        file.read(bytes, buffer.byteLength);
        file.close();

        buffers.push_back(bytes);
    }

    std::vector<ImageRGB> images;

    for (const auto& image : doc.images)
    {
        images.push_back(ImageUtils::loadImage(image.uri));
    }

    for (const auto& scene : doc.scenes)
    {
        for (int rootNodeIndex : scene.nodes)
        {
            const gltf::Node& rootNode = doc.nodes[rootNodeIndex];

            glm::mat4 matrix = glm::mat4(1.0f);
            SceneData sceneData;
            traverse(rootNode, matrix, sceneData);
        }
    }

    for (char* buffer : buffers)
        delete[] buffer;
}
