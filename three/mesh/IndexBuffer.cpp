#include "IndexBuffer.h"

namespace three
{

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    :
    BufferObject(std::move(other)),
    dataType(other.dataType),
    indexCount(other.indexCount)
{
    other.indexCount = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    BufferObject::operator=(std::move(other));
    dataType = other.dataType;
    indexCount = other.indexCount;
    other.indexCount = 0;
    return *this;
}

void IndexBuffer::draw(GLenum primitiveType, GLenum dataType, int indexCount)
{
    glDrawElements(primitiveType, indexCount, dataType, nullptr);
}

void IndexBuffer::draw(GLenum primitiveType) const
{
    draw(primitiveType, dataType, indexCount);
}

void IndexBuffer::allocate(GLenum dataType, int indexSize, int indexCount, const void* data, GLenum usage)
{
    BufferObject::allocate(indexSize * indexCount, data, usage);
    this->dataType = dataType;
    this->indexCount = indexCount;
}

}
