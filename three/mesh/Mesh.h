#pragma once

#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "AttributeBindings.h"

namespace three
{

class Mesh
{
public:
    static Mesh create(
        const VertexBuffer& vertexBuffer,
        const AttributeBindings& bindings,
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
