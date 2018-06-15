#include "ShaderProgram.h"

#include <sstream>

#include "Shader.h"
#include "UniformBuffer.h"
#include "AttributeInfo.h"

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

GLuint ShaderProgram::getHandle() const {
    return program;
}

void ShaderProgram::attachShader(const Shader& shader) {
    glAttachShader(program, shader.getHandle());
}

void ShaderProgram::detachShader(const Shader& shader) {
    glDetachShader(program, shader.getHandle());
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

void ShaderProgram::use() {
    glUseProgram(program);
}

int ShaderProgram::getAttributeLocation(const std::string& name) const {
    return glGetAttribLocation(program, name.c_str());
}

int ShaderProgram::getUniformLocation(const std::string& name) const {
    return glGetUniformLocation(program, name.c_str());
}

void ShaderProgram::bindUniformBlock(const std::string& name, const UniformBuffer& buffer) {
    const auto index = glGetUniformBlockIndex(program, name.c_str());
    assert(index != GL_INVALID_INDEX);
    glUniformBlockBinding(program, index, buffer.getBindingPoint());
    assert(glGetError() == GL_NO_ERROR);
}

std::vector<AttributeInfo> ShaderProgram::getActiveAttributes() const {
    std::vector<AttributeInfo> attributes;

    int count;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);

    const GLsizei nameBuffSize = 16;
    GLchar name[nameBuffSize];

    for (auto i = 0; i < count; i++) {
        GLint size;
        GLenum type;
        GLsizei length;
        glGetActiveAttrib(program, i, nameBuffSize, &length, &size, &type, name);

        AttributeInfo attribInfo;
        attribInfo.name = name;
        attribInfo.dataType = type;
        attribInfo.location = getAttributeLocation(name);
        attributes.push_back(attribInfo);
    }

    return attributes;
}

}
