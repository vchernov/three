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

void from_json(const json& j, Document& doc)
{
    j.at("buffers").get_to(doc.buffers);
    j.at("images").get_to(doc.images);
    j.at("bufferViews").get_to(doc.bufferViews);
}

}
