#include "UniformBuffer.h"

#include <cstring>
#include <algorithm>

namespace three {

unsigned int UniformBuffer::nextBlockId = 0;

UniformBuffer::UniformBuffer() {
    blockId = nextBlockId++;
}

UniformBuffer::UniformBuffer(UniformBuffer&& other) noexcept
    :
    BufferObject(std::move(other)),
    blockId(other.blockId) {
    other.blockId = -1;
}

UniformBuffer& UniformBuffer::operator=(UniformBuffer&& other) noexcept {
    BufferObject::operator=(std::move(other));
    blockId = other.blockId;
    other.blockId = -1;
    return *this;
}

void UniformBuffer::bindBlock() {
    BufferObject::bindBlock(blockId);
}

void UniformBuffer::write(void* data, int offset, int length) {
    void* ptr = mapRange(offset, length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
    assert(ptr != nullptr);
    memcpy(ptr, data, length);
    BufferObject::unmap();
}

}
