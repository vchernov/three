#pragma once

#include "BufferObject.h"

namespace three {

class IndexBuffer : public BufferObject<GL_ELEMENT_ARRAY_BUFFER> {
public:
    IndexBuffer() = default;

    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    static void draw(unsigned int primitiveType, unsigned int dataType, int indexCount);

    void draw(unsigned int primitiveType) const;

    unsigned int getDataType() const;
    int getIndexCount() const;

    void upload(const void* data, unsigned int dataType, int indexSize, int indexCount, unsigned int usage = GL_STATIC_DRAW);

private:
    unsigned int dataType = GL_UNSIGNED_SHORT;
    int indexCount = 0;
};

}
