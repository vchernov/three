#include "UniformBuffer.h"

#include <cstring>

namespace three {

unsigned int UniformBuffer::nextBlockId = 0;

UniformBuffer::UniformBuffer() {
    blockId = nextBlockId++;
}

void UniformBuffer::bindBlock() {
    BufferObject::bindBlock(blockId);
}

void UniformBuffer::allocate(int size) {
    upload(nullptr, size, GL_DYNAMIC_DRAW);
}

void UniformBuffer::write(void* data, int offset, int length) {
    void* ptr = mapRange(offset, length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
    memcpy(ptr, data, length);
    BufferObject::unmap();
}

}
