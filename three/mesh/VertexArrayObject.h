#pragma once

#include <GL/glew.h>

namespace three {

class VertexArrayObject {
public:
    VertexArrayObject();
    virtual ~VertexArrayObject();

    VertexArrayObject(const VertexArrayObject&) = delete;
    VertexArrayObject& operator=(const VertexArrayObject&) = delete;

    VertexArrayObject(VertexArrayObject&& other) noexcept;
    VertexArrayObject& operator=(VertexArrayObject&& other) noexcept;

    void bind() const;
    static void unbind();

private:
    GLuint vao;
};

}
