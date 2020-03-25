#include "gltf.h"

namespace gltf
{

void from_json(const json& j, Buffer& buffer)
{
    j.at("byteLength").get_to(buffer.byteLength);
    j.at("uri").get_to(buffer.uri);
}

void from_json(const json& j, Image& image)
{
    j.at("uri").get_to(image.uri);
}

void from_json(const json& j, BufferView& bufferView)
{
    j.at("buffer").get_to(bufferView.buffer);
    j.at("byteOffset").get_to(bufferView.byteOffset);
    j.at("byteLength").get_to(bufferView.byteLength);
    j.at("target").get_to(bufferView.target);
}

void from_json(const json& j, Accessor& accessor)
{
    j.at("bufferView").get_to(accessor.bufferView);
    if (j.find("byteOffset") != j.end())
        j.at("byteOffset").get_to(accessor.byteOffset);
    else
        accessor.byteOffset = 0;
    j.at("componentType").get_to(accessor.componentType);
    j.at("count").get_to(accessor.count);
    j.at("type").get_to(accessor.type);
}

void from_json(const json& j, Primitive& primitive)
{
}

void from_json(const json& j, Mesh& mesh)
{
}

void from_json(const json& j, Node& node)
{
    if (j.find("mesh") != j.end())
        j.at("mesh").get_to(node.mesh);
    else
        node.mesh = -1;

    if (j.find("children") != j.end())
        j.at("children").get_to(node.children);

    node.hasTransform = false;

    if (j.find("translation") != j.end())
    {
        j.at("translation").get_to(node.translation);
        node.hasTransform = true;
    }
    else
    {
        std::fill(std::begin(node.translation), std::end(node.translation), 0.0f);
    }

    if (j.find("rotation") != j.end())
    {
        j.at("rotation").get_to(node.rotation);
        node.hasTransform = true;
    }
    else
    {
        node.rotation = {0.0f, 0.0f, 0.0f, 1.0f};
    }

    if (j.find("scale") != j.end())
    {
        j.at("scale").get_to(node.scale);
        node.hasTransform = true;
    }
    else
    {
        std::fill(std::begin(node.scale), std::end(node.scale), 1.0f);
    }

    node.hasMatrix = false;
    if (j.find("matrix") != j.end())
    {
        j.at("matrix").get_to(node.matrix);
        node.hasMatrix = true;
    }
}

void from_json(const json& j, Scene& scene)
{
    j.at("nodes").get_to(scene.nodes);
}

void from_json(const json& j, Document& doc)
{
    j.at("buffers").get_to(doc.buffers);
    j.at("images").get_to(doc.images);
    j.at("bufferViews").get_to(doc.bufferViews);
    j.at("accessors").get_to(doc.accessors);
    j.at("meshes").get_to(doc.meshes);
    j.at("nodes").get_to(doc.nodes);
    j.at("scenes").get_to(doc.scenes);
}

}
