#pragma once

#include <cassert>
#include <vector>
#include <list>

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

    static void allocate(int size, const void* data = nullptr, GLenum usage = GL_STATIC_DRAW) {
        glBufferData(target, size, data, usage);
        assert(glGetError() == GL_NO_ERROR);
    }

    template<typename T>
    static void allocate(const std::vector<T>& container, GLenum usage = GL_STATIC_DRAW) {
        allocate(container.size() * sizeof(T), container.data(), usage);
    }

    template<typename T, size_t size>
    static void allocate(const std::array<T, size>& container, GLenum usage = GL_STATIC_DRAW) {
        allocate(container.size() * sizeof(T), container.data(), usage);
    }

    void static upload(int offset, int size, const void* data) {
        glBufferSubData(target, offset, size, data);
        assert(glGetError() == GL_NO_ERROR);
    }

    template<typename T>
    static void upload(int offset, const std::vector<T>& container) {
        upload(offset, container.size() * sizeof(T), container.data());
    }

    template<typename T, size_t size>
    static void upload(int offset, const std::array<T, size>& container) {
        upload(offset, container.size() * sizeof(T), container.data());
    }

protected:
    void bindBlock(unsigned int blockId) const {
        glBindBufferBase(target, blockId, buffer);
    }

    static void* mapRange(int offset, int length, unsigned int access) {
        return glMapBufferRange(target, offset, length, access);
    }

    static void unmap() {
        glUnmapBuffer(target);
    }

private:
    GLuint buffer;
};

}
