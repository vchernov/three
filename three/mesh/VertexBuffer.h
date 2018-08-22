#pragma once

#include "../BufferObject.h"

namespace three
{

class VertexBuffer : public BufferObject<GL_ARRAY_BUFFER>
{
public:
    static void draw(GLenum primitiveType, int first, int count);
};

}
