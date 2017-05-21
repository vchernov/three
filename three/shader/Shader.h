#pragma once

#include <string>

#include <GL/glew.h>

namespace three {

class Shader {
public:
    friend class ShaderProgram;

    Shader(const std::string& source, GLenum type);
    virtual ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    bool getCompileStatus() const;
    std::string getInfoLog() const;

private:
    GLuint shader;
};

class VertexShader : public Shader {
public:
    explicit VertexShader(const std::string& source);
};

class FragmentShader : public Shader {
public:
    explicit FragmentShader(const std::string& source);
};

class GeometryShader : public Shader {
public:
    explicit GeometryShader(const std::string& source);
};

}
