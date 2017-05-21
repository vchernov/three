#pragma once

#include <vector>
#include <list>

#include "BufferObject.h"
#include "VertexAttribute.h"
#include "../shader/ShaderProgram.h"

namespace three {

class VertexBuffer : public BufferObject<GL_ARRAY_BUFFER> {
public:
    VertexBuffer() = default;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    static void draw(unsigned int primitiveType, int first, int count);

    void draw(unsigned int primitiveType) const;

    int getVertexCount() const;

    void addAttribute(VertexAttribute attribute);
    void enableAttributes(const ShaderProgram& shaderProg) const;

    void upload(const void* data, int vertexCount, int stride, unsigned int usage = GL_STATIC_DRAW);

    template<typename T>
    void upload(const std::vector<T>& container, unsigned int usage = GL_STATIC_DRAW) {
        upload(container.data(), container.size(), sizeof(T), usage);
    }

    template<typename T>
    void addAttribute(std::string name, int offset);

private:
    int vertexCount = 0;
    int stride = 0;
    std::list<VertexAttribute> attributes;
};

}
