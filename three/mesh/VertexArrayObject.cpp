#include "VertexArrayObject.h"

namespace three {

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &vao);
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &vao);
}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) noexcept
    : vao(other.vao) {
    other.vao = 0;
}

VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& other) noexcept {
    vao = other.vao;
    other.vao = 0;
    return *this;
}

void VertexArrayObject::bind() const {
    glBindVertexArray(vao);
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
}

}
