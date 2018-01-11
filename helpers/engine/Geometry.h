#pragma once

#include <vector>

#include <GL/glew.h>

template<typename VertexType, typename FaceType>
struct Geometry {
    std::vector<VertexType> vertices;
    std::vector<FaceType> faces;
    GLenum primitiveType = GL_TRIANGLES;
};
