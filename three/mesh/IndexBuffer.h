#pragma once

#include "../BufferObject.h"

namespace three {

class IndexBuffer : public BufferObject<GL_ELEMENT_ARRAY_BUFFER> {
public:
    IndexBuffer() = default;

    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    static void draw(GLenum primitiveType, GLenum dataType, int indexCount);

    void draw(GLenum primitiveType) const;

    void allocate(GLenum dataType, int indexSize, int indexCount, const void* data, GLenum usage = GL_STATIC_DRAW);

private:
    GLenum dataType = GL_UNSIGNED_SHORT;
    int indexCount = 0;
};

}
