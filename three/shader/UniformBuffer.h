#pragma once

#include "../BufferObject.h"

namespace three {

class UniformBuffer : public BufferObject<GL_UNIFORM_BUFFER> {
public:
    UniformBuffer();

    GLuint getBindingPoint() const;

    void bindBindingPoint();

    static void write(void* data, int offset, int length);

private:
    static GLuint nextBindingPoint;

    GLuint bindingPoint;
};

}
