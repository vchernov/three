#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

namespace three {

class Shader;
class UniformBuffer;
struct AttributeInfo;

class ShaderProgram {
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    GLuint getHandle() const;

    void attachShader(const Shader& shader);
    void detachShader(const Shader& shader);

    void link();

    bool getLinkStatus() const;
    std::string getInfoLog() const;

    virtual void use();

    int getAttributeLocation(const std::string& name) const;

    int getUniformLocation(const std::string& name) const;

    void bindUniformBlock(const std::string& name, const UniformBuffer& buffer);

    std::vector<AttributeInfo> getActiveAttributes() const;

protected:
    GLuint program;
};

}
