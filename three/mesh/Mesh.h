#pragma once

#include <vector>

#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace three {

class Mesh {
public:
    static Mesh create(
        const VertexBuffer& vertexBuffer,
        std::vector<VertexAttribute> attributes,
        IndexBuffer indexBuffer,
        GLenum primitiveType = GL_TRIANGLES);

    virtual ~Mesh() = default;

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&&) noexcept = default;
    Mesh& operator=(Mesh&&) = default;

    void draw() const;

private:
    Mesh(IndexBuffer indexBuffer, GLenum primitiveType);

    VertexArrayObject vao;
    IndexBuffer indexBuffer;
    GLenum primitiveType;
};

}
