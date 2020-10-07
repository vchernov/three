#include "ModelLoader.h"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BufferHolder.h"
#include "gltf.h"

#include "../../three/transform/ModelTransform.h"
#include "../../three/transform/Transform.h"

#include "../../helpers/engine/Model.h"
#include "../../helpers/engine/fs/ChangeDir.h"
#include "../../helpers/engine/fs/FileNotFoundException.h"
#include "../../helpers/engine/fs/FileSystem.h"
#include "../../helpers/engine/scene/ITransform.h"
#include "../../helpers/engine/scene/TransformComponent.h"

#include "../../helpers/image/ImageUtils.h"

using namespace three;
using json = nlohmann::json;
using BinBufferHolder = BufferHolder<char>;

struct Content
{
    gltf::Document document;
    std::vector<BinBufferHolder> buffers;
    std::vector<ImageRGB> images;
};

void processElements(const gltf::Node& node, const Content& content, Node& target)
{
    if (node.hasTransform)
    {
        auto transformComponent = std::make_unique<TransformComponent<three::ModelTransform>>();
        auto& transform = transformComponent->transform;

        transform.position = glm::make_vec3(node.translation.data());
        transform.rotation = glm::make_quat(node.rotation.data());
        transform.scale = glm::make_vec3(node.scale.data());

        target.transforms.push_back(std::move(transformComponent));
    }

    if (node.hasMatrix)
    {
        auto transformComponent = std::make_unique<TransformComponent<three::Transform>>();
        auto& transform = transformComponent->transform;

        transform.set(glm::make_mat4(node.matrix.data()));

        target.transforms.push_back(std::move(transformComponent));
    }

    if (node.mesh >= 0 && node.mesh < content.document.meshes.size())
    {
    }
}

void traverse(const gltf::Node& node, const Content& content, Node& target)
{
    processElements(node, content, target);

    for (int nodeIndex : node.children)
    {
        const gltf::Node& child = content.document.nodes[nodeIndex];
        Node newNode;
        traverse(child, content, newNode);
        target.children.push_back(std::move(newNode));
    }
}

std::vector<Scene> ModelLoader::loadModel(const std::string& fn)
{
    std::ifstream gltfFile(fn);
    if (!gltfFile.is_open())
        throw FileNotFoundException(fn);

    json j = json::parse(gltfFile);
    gltfFile.close();

    Content content;
    content.document = j.get<gltf::Document>();

    ChangeDir cd{FileSystem::getFilePath(fn)};

    for (const auto& buffer : content.document.buffers)
    {
        std::fstream file(buffer.uri, std::ios::in | std::ios::binary);
        if (!file.is_open())
            throw FileNotFoundException(buffer.uri);

        char* bytes = new char[buffer.byteLength];
        file.read(bytes, buffer.byteLength);
        file.close();

        content.buffers.push_back(BinBufferHolder(bytes));
    }

    for (const auto& image : content.document.images)
    {
        content.images.push_back(ImageUtils::loadImage(image.uri));
    }

    std::vector<Scene> scenes;

    for (const auto& scene : content.document.scenes)
    {
        for (int rootNodeIndex : scene.nodes)
        {
            const gltf::Node& root = content.document.nodes[rootNodeIndex];
            Scene scene;
            traverse(root, content, scene.root);
            scenes.push_back(std::move(scene));
        }
    }

    return scenes;
}
