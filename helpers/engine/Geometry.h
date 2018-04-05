#pragma once

#include <vector>

#include <GL/glew.h>

template<typename VertexType, typename FaceType>
struct Geometry {
    using Vertex = VertexType;
    using Face = FaceType;

    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    GLenum primitiveType = GL_TRIANGLES;
};
