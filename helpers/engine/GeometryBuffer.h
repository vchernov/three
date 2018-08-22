#pragma once

#include <vector>

#include <GL/glew.h>

#include "../../three/mesh/VertexBuffer.h"
#include "../../three/mesh/VertexAttribute.h"
#include "../../three/mesh/IndexBuffer.h"

struct GeometryBuffer
{
    three::VertexBuffer vertexBuffer;
    std::vector<three::VertexAttribute> attributes;
    three::IndexBuffer indexBuffer;
    unsigned int primitiveType = GL_TRIANGLES;
};
