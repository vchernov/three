#pragma once

#include <array>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace gltf
{

struct Buffer
{
    size_t byteLength;
    std::string uri;
};

void from_json(const json& j, Buffer& buffer);

struct Image
{
    std::string uri;
};

void from_json(const json& j, Image& image);

struct BufferView
{
    int buffer;
    size_t byteOffset;
    size_t byteLength;
    unsigned int target;
};

void from_json(const json& j, BufferView& bufferView);

struct Accessor
{
    int bufferView;
    size_t byteOffset;
    unsigned int componentType;
    int count;
    std::string type;
};

void from_json(const json& j, Accessor& accessor);

struct Primitive
{
    std::vector<int> indices;
};

void from_json(const json& j, Primitive& primitive);

struct Mesh
{
};

void from_json(const json& j, Mesh& mesh);

struct Node
{
    int mesh;
    std::vector<int> children;
    std::array<float, 3> translation;
    std::array<float, 4> rotation;
    std::array<float, 3> scale;
};

void from_json(const json& j, Node& node);

struct Scene
{
    std::vector<int> nodes;
};

void from_json(const json& j, Scene& scene);

struct Document
{
    std::vector<Buffer> buffers;
    std::vector<Image> images;
    std::vector<BufferView> bufferViews;
    std::vector<Accessor> accessors;
    std::vector<Mesh> meshes;
    std::vector<Node> nodes;
    std::vector<Scene> scenes;
};

void from_json(const json& j, Document& doc);

}
