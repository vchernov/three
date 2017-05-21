#pragma once

#include <list>

#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace three {

class Mesh {
public:
    static Mesh create(
        const VertexBuffer& vertexBuffer,
        IndexBuffer indexBuffer,
        const ShaderProgram& shaderProg,
        unsigned int primitiveType = GL_TRIANGLES);

    static Mesh create(
        const std::list<VertexBuffer>& vertexBuffers,
        IndexBuffer indexBuffer,
        const ShaderProgram& shaderProg,
        unsigned int primitiveType = GL_TRIANGLES);

    virtual ~Mesh() = default;

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&&) noexcept = default;
    Mesh& operator=(Mesh&&) = default;

    void draw() const;

private:
    explicit Mesh(IndexBuffer indexBuffer, unsigned int primitiveType);

    VertexArrayObject vao;
    IndexBuffer indexBuffer;
    unsigned int primitiveType;
};

}
