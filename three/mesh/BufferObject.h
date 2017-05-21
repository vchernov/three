#pragma once

#include <cassert>

#include <GL/glew.h>

namespace three {

template<GLenum target>
class BufferObject {
public:
    BufferObject() {
        glGenBuffers(1, &buffer);
    }

    virtual ~BufferObject() {
        glDeleteBuffers(1, &buffer);
    }

    BufferObject(const BufferObject&) = delete;
    BufferObject& operator=(const BufferObject&) = delete;

    BufferObject(BufferObject&& other) noexcept
        : buffer(other.buffer) {
        other.buffer = 0;
    }

    BufferObject& operator=(BufferObject&& other) noexcept {
        buffer = other.buffer;
        other.buffer = 0;
        return *this;
    }

    void bind() const {
        glBindBuffer(target, buffer);
    }

    static void unbind() {
        glBindBuffer(target, 0);
    }

protected:
    void static upload(const void* data, size_t length, unsigned int usage) {
        glBufferData(target, length, data, usage);
        assert(glGetError() == GL_NO_ERROR);
    }

private:
    GLuint buffer;
};

}
