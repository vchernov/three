#include "Mesh.h"

namespace three {

Mesh::Mesh(IndexBuffer indexBuffer, GLenum primitiveType)
    :
    indexBuffer(std::move(indexBuffer)),
    primitiveType(primitiveType) {
}

void Mesh::draw() const {
    vao.bind();
    indexBuffer.draw(primitiveType);
    VertexArrayObject::unbind();
}

Mesh Mesh::create(
    const VertexBuffer& vertexBuffer,
    const AttributeBindings& bindings,
    IndexBuffer indexBuffer,
    GLenum primitiveType) {
    Mesh mesh(std::move(indexBuffer), primitiveType);
    mesh.vao.bind();
    vertexBuffer.bind();
    for (const auto& attribute : bindings.attributes) {
        mesh.vao.registerAttribute(attribute);
        mesh.vao.enableAttribute(attribute.location);
    }
    mesh.indexBuffer.bind();
    VertexArrayObject::unbind();
    return mesh;
}

}
