#include "Mesh.h"

namespace three {

Mesh::Mesh(IndexBuffer indexBuffer, unsigned int primitiveType)
    :
    indexBuffer(std::move(indexBuffer)),
    primitiveType(primitiveType) {
}

Mesh Mesh::create(
    const VertexBuffer& vertexBuffer,
    IndexBuffer indexBuffer,
    const ShaderProgram& shaderProg,
    unsigned int primitiveType) {
    Mesh mesh(std::move(indexBuffer), primitiveType);
    mesh.vao.bind();
    vertexBuffer.bind();
    vertexBuffer.enableAttributes(shaderProg);
    mesh.indexBuffer.bind();
    VertexArrayObject::unbind();
    return mesh;
}

Mesh Mesh::create(
    const std::list<VertexBuffer>& vertexBuffers,
    IndexBuffer indexBuffer,
    const ShaderProgram& shaderProg,
    unsigned int primitiveType) {
    Mesh mesh(std::move(indexBuffer), primitiveType);
    mesh.vao.bind();
    for (const auto& vb : vertexBuffers) {
        vb.bind();
        vb.enableAttributes(shaderProg);
    }
    mesh.indexBuffer.bind();
    VertexArrayObject::unbind();
    return mesh;
}

void Mesh::draw() const {
    vao.bind();
    indexBuffer.draw(primitiveType);
    VertexArrayObject::unbind();
}

}
