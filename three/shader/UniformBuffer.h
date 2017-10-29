#pragma once

#include "../BufferObject.h"

namespace three {

class UniformBuffer : public BufferObject<GL_UNIFORM_BUFFER> {
public:
    friend class ShaderProgram;

    UniformBuffer();

    void bindBlock();

    void allocate(int size);

    void write(void* data, int offset, int length);

private:
    static unsigned int nextBlockId;

    unsigned int blockId;
};

}
