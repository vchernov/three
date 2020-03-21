#pragma once

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

struct Document
{
    std::vector<Buffer> buffers;
    std::vector<Image> images;
    std::vector<BufferView> bufferViews;
};

void from_json(const json& j, Document& doc);

}
