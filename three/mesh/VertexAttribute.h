#pragma once

#include <GL/glew.h>

namespace three {

struct AttributeInfo;

struct VertexAttribute {
    VertexAttribute(
        GLuint location,
        GLenum dataType,
        int componentCount,
        int offset,
        int stride,
        bool normalized = false);

    const GLuint location;
    const GLenum dataType;
    const int componentCount;
    const int offset;
    const int stride;
    const bool normalized;

    template<typename T>
    static VertexAttribute create(int location, int componentCount, int offset, int stride);

    template<typename T>
    static VertexAttribute create(int location, int offset, int stride);

    template<typename T>
    static VertexAttribute create(const AttributeInfo& info, int offset, int stride);
};

}
