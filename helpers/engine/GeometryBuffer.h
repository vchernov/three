#pragma once

#include <list>

#include <GL/glew.h>

#include "../../three/mesh/VertexBuffer.h"
#include "../../three/mesh/IndexBuffer.h"

struct GeometryBuffer {
    std::list<three::VertexBuffer> vertexBuffers;
    three::IndexBuffer indexBuffer;
    unsigned int primitiveType = GL_TRIANGLES;
};
