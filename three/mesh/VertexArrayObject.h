#pragma once

#include "VertexAttribute.h"

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

    static void enableAttribute(int index);
    static void disableAttribute(int index);

    static void registerAttribute(const VertexAttribute& attribute);

private:
    GLuint vao;
};

}
