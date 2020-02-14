#include "ShaderUtils.h"

#include <iostream>
#include <cassert>

#include "fs/FileSystem.h"

#include "../../three/shader/Shader.h"

void ShaderUtils::loadShaderProgram(
    three::ShaderProgram* program,
    const std::string& vertFileName,
    const std::string& fragFileName)
{
    assert(program != nullptr);

    three::VertexShader vert(FileSystem::readFile(vertFileName));
    std::cout << vertFileName << " = " << vert.getCompileStatus() << " " << vert.getInfoLog() << std::endl;

    three::FragmentShader frag(FileSystem::readFile(fragFileName));
    std::cout << fragFileName << " = " << frag.getCompileStatus() << " " << frag.getInfoLog() << std::endl;

    program->attachShader(vert);
    program->attachShader(frag);
    program->link();

    std::cout << vertFileName << " + " << fragFileName << " = " << program->getLinkStatus();
    std::cout << " " << program->getInfoLog();
    std::cout << std::endl;
}

three::ShaderProgram ShaderUtils::loadShaderProgram(
    const std::string& vertFileName,
    const std::string& fragFileName)
{
    three::ShaderProgram program;
    loadShaderProgram(&program, vertFileName, fragFileName);
    return program;
}
