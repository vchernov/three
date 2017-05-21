#include "Shader.h"

#include <sstream>

namespace three {

Shader::Shader(const std::string& source, GLenum type) {
    shader = glCreateShader(type);
    GLchar const* srcBuff[] = {source.c_str()};
    glShaderSource(shader, 1, srcBuff, nullptr);
    glCompileShader(shader);
}

Shader::~Shader() {
    glDeleteShader(shader);
}

Shader::Shader(Shader&& other) noexcept
    : shader(other.shader) {
    other.shader = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    shader = other.shader;
    other.shader = 0;
    return *this;
}

bool Shader::getCompileStatus() const {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
}

std::string Shader::getInfoLog() const {
    std::stringstream ss;
    GLint infoLogLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 1) {
        char* infoLog = new char[infoLogLen];
        glGetShaderInfoLog(shader, infoLogLen, nullptr, infoLog);
        ss << infoLog;
        delete[] infoLog;
    }
    return ss.str();
}

VertexShader::VertexShader(const std::string& source)
    : Shader(source, GL_VERTEX_SHADER) {
}

FragmentShader::FragmentShader(const std::string& source)
    : Shader(source, GL_FRAGMENT_SHADER) {
}

GeometryShader::GeometryShader(const std::string& source)
    : Shader(source, GL_GEOMETRY_SHADER) {
}

}
