#pragma once

#include <GL/glew.h>

namespace three
{

template<GLenum target>
class Texture
{
public:
    Texture()
    {
        glGenTextures(1, &texture);
    }

    virtual ~Texture()
    {
        glDeleteTextures(1, &texture);
    }

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept
        :
        texture(other.texture)
    {
        other.texture = 0;
    }

    Texture& operator=(Texture&& other) noexcept
    {
        texture = other.texture;
        other.texture = 0;
        return *this;
    }

    void bind() const
    {
        glBindTexture(target, texture);
    }

    static void unbind()
    {
        glBindTexture(target, 0);
    }

    static void generateMipmap()
    {
        glGenerateMipmap(target);
    }

    static void setFiltering(GLint minFilter, GLint magFilter)
    {
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
    }

    static void setWrapping(GLint sWrap, GLint tWrap)
    {
        glTexParameteri(target, GL_TEXTURE_WRAP_S, sWrap);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, tWrap);
    }

private:
    GLuint texture;
};

}
