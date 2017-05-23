#include "ShaderProgram.h"

#include <sstream>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

namespace three {

ShaderProgram::ShaderProgram() {
    program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    : program(other.program) {
    other.program = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
    program = other.program;
    other.program = 0;
    return *this;
}

void ShaderProgram::attachShader(const Shader& shader) {
    glAttachShader(program, shader.shader);
}

void ShaderProgram::detachShader(const Shader& shader) {
    glDetachShader(program, shader.shader);
}

void ShaderProgram::link() {
    glLinkProgram(program);
}

bool ShaderProgram::getLinkStatus() const {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    return status == GL_TRUE;
}

std::string ShaderProgram::getInfoLog() const {
    std::stringstream ss;
    GLint infoLogLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 1) {
        char* infoLog = new char[infoLogLen];
        glGetProgramInfoLog(program, infoLogLen, nullptr, infoLog);
        ss << infoLog;
        delete[] infoLog;
    }
    return ss.str();
}

void ShaderProgram::use() const {
    glUseProgram(program);
}

int ShaderProgram::getAttributeLocation(const std::string& name) const {
    return glGetAttribLocation(program, name.c_str());
}

int ShaderProgram::getUniformLocation(const std::string& name) const {
    return glGetUniformLocation(program, name.c_str());
}

template<>
void ShaderProgram::setUniform(int location, float value) {
    glUniform1f(location, value);
}

template<>
void ShaderProgram::setUniform(int location, int value) {
    glUniform1i(location, value);
}

template<>
void ShaderProgram::setUniform(int location, glm::vec3 value) {
    glUniform3fv(location, 1, glm::value_ptr(value));
}

template<>
void ShaderProgram::setUniform(int location, glm::mat4 value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

}
