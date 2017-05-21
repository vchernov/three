#include "IndexBuffer.h"

#include <algorithm>

namespace three {

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    :
    BufferObject(std::move(other)),
    dataType(other.dataType),
    indexCount(other.indexCount) {
    other.indexCount = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
    BufferObject::operator=(std::move(other));
    dataType = other.dataType;
    indexCount = other.indexCount;
    other.indexCount = 0;
    return *this;
}

void IndexBuffer::draw(unsigned int primitiveType, unsigned int dataType, int indexCount) {
    glDrawElements(primitiveType, indexCount, dataType, nullptr);
}

void IndexBuffer::draw(unsigned int primitiveType) const {
    draw(primitiveType, dataType, indexCount);
}

unsigned int IndexBuffer::getDataType() const {
    return dataType;
}

int IndexBuffer::getIndexCount() const {
    return indexCount;
}

void IndexBuffer::upload(const void* data, unsigned int dataType, int indexSize, int indexCount, unsigned int usage) {
    BufferObject::upload(data, indexSize * indexCount, usage);
    this->dataType = dataType;
    this->indexCount = indexCount;
}

}
