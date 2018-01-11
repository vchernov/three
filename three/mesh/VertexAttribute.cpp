#include "VertexAttribute.h"

#include "../TypeInfo.h"
#include "../shader/AttributeInfo.h"

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace three {

VertexAttribute::VertexAttribute(
    int location,
    GLenum dataType,
    int numComponents,
    int offset,
    int stride,
    bool normalized)
    :
    location(location),
    dataType(dataType),
    componentCount(numComponents),
    offset(offset),
    stride(stride),
    normalized(normalized) {
}

template<>
VertexAttribute VertexAttribute::create<float>(int location, int numComponents, int offset, int stride) {
    return VertexAttribute(location, TypeInfo<float>::dataType, numComponents, offset, stride, false);
}

template<>
VertexAttribute VertexAttribute::create<glm::vec2>(const AttributeInfo& info, int offset, int stride) {
    assert(info.dataType == GL_FLOAT_VEC2);
    return create<glm::vec2::value_type>(info.location, glm::vec2::length(), offset, stride);
}

template<>
VertexAttribute VertexAttribute::create<glm::vec3>(const AttributeInfo& info, int offset, int stride) {
    assert(info.dataType == GL_FLOAT_VEC3);
    return create<glm::vec3::value_type>(info.location, glm::vec3::length(), offset, stride);
}

}
