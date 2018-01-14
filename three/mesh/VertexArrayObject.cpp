#include "VertexArrayObject.h"

#include <cassert>

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

void VertexArrayObject::enableAttribute(GLuint index) {
    glEnableVertexAttribArray(index);
    assert(glGetError() == GL_NO_ERROR);
}

void VertexArrayObject::disableAttribute(GLuint index) {
    glDisableVertexAttribArray(index);
    assert(glGetError() == GL_NO_ERROR);
}

void VertexArrayObject::registerAttribute(const VertexAttribute& attribute) {
    glVertexAttribPointer(
        attribute.location,
        attribute.componentCount,
        attribute.dataType,
        attribute.normalized ? GL_TRUE : GL_FALSE,
        attribute.stride,
        reinterpret_cast<GLvoid*>(attribute.offset));
}

}
