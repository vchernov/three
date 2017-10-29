#include "VertexBuffer.h"

#include <glm/glm.hpp>

#include "../TypeInfo.h"

namespace three {

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    :
    BufferObject(std::move(other)),
    vertexCount(other.vertexCount),
    stride(other.stride),
    attributes(std::move(other.attributes)) {
    other.vertexCount = 0;
    other.stride = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
    BufferObject::operator=(std::move(other));
    vertexCount = other.vertexCount;
    stride = other.stride;
    other.vertexCount = 0;
    other.stride = 0;
    attributes = std::move(other.attributes);
    return *this;
}

void VertexBuffer::draw(unsigned int primitiveType, int first, int count) {
    glDrawArrays(primitiveType, first, count);
}

void VertexBuffer::draw(unsigned int primitiveType) const {
    draw(primitiveType, 0, vertexCount);
}

int VertexBuffer::getVertexCount() const {
    return vertexCount;
}

void VertexBuffer::addAttribute(VertexAttribute attribute) {
    attributes.push_back(attribute);
}

void VertexBuffer::enableAttributes(const ShaderProgram& shaderProg) const {
    for (const auto& attrib : attributes) {
        auto location = shaderProg.getAttributeLocation(attrib.name);
        //*
        if (location < 0) {
            continue;
        }
        /*/
        assert(location >= 0);
        //*/
        glVertexAttribPointer(location, attrib.size, attrib.dataType, attrib.normalize ? GL_TRUE : GL_FALSE, stride, (GLvoid*)attrib.offset);
        assert(glGetError() == GL_NO_ERROR);
        glEnableVertexAttribArray(location);
        assert(glGetError() == GL_NO_ERROR);
    }
}

void VertexBuffer::upload(const void* data, int vertexCount, int stride, unsigned int usage) {
    BufferObject::upload(data, vertexCount * stride, usage);
    this->vertexCount = vertexCount;
    this->stride = stride;
}

template<>
void VertexBuffer::addAttribute<glm::vec2>(std::string name, int offset) {
    addAttribute({name, TypeInfo<glm::vec2::value_type>::dataType, glm::vec2::length(), offset});
}

template<>
void VertexBuffer::addAttribute<glm::vec3>(std::string name, int offset) {
    addAttribute({name, TypeInfo<glm::vec3::value_type>::dataType, glm::vec3::length(), offset});
}

}
