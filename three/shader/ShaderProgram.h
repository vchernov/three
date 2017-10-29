#pragma once

#include <string>

#include <GL/glew.h>

namespace three {

class Shader;
class UniformBuffer;

class ShaderProgram {
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    void attachShader(const Shader& shader);
    void detachShader(const Shader& shader);

    void link();

    bool getLinkStatus() const;
    std::string getInfoLog() const;

    void use() const;

    int getAttributeLocation(const std::string& name) const;

    int getUniformLocation(const std::string& name) const;

    int getUniformBlockIndex(const std::string& name) const;

    void bindUniformBlock(const std::string& name, const UniformBuffer& buffer);

    template<class T>
    void setUniform(int location, T value);

protected:
    GLuint program;
};

}
