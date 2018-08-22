#include "UniformBuffer.h"

#include <string.h>

namespace three
{

GLuint UniformBuffer::nextBindingPoint = 0;

UniformBuffer::UniformBuffer()
{
    bindingPoint = nextBindingPoint++;
    bindBindingPoint();
}

GLuint UniformBuffer::getBindingPoint() const
{
    return bindingPoint;
}

void UniformBuffer::bindBindingPoint()
{
    BufferObject::bindBindingPoint(bindingPoint);
}

void UniformBuffer::write(void* data, int offset, int length)
{
    void* ptr = mapRange(offset, length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
    assert(ptr != nullptr);
    memcpy(ptr, data, length);
    unmap();
}

}
