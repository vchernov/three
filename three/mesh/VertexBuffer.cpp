#include "VertexBuffer.h"

namespace three
{

void VertexBuffer::draw(GLenum primitiveType, int first, int count)
{
    glDrawArrays(primitiveType, first, count);
}

}
