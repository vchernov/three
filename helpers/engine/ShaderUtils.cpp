#include "ShaderUtils.h"

#include <iostream>

#include "FileSystem.h"

#include "../../three/shader/Shader.h"

three::ShaderProgram ShaderUtils::loadShaderProgram(const std::string& vertFileName, const std::string& fragFileName) {
    three::VertexShader vert(FileSystem::readFile(vertFileName));
    std::cout << vertFileName << " = " << vert.getCompileStatus() << " " << vert.getInfoLog() << std::endl;

    three::FragmentShader frag(FileSystem::readFile(fragFileName));
    std::cout << fragFileName << " = " << frag.getCompileStatus() << " " << frag.getInfoLog() << std::endl;

    three::ShaderProgram shaderProg;
    shaderProg.attachShader(vert);
    shaderProg.attachShader(frag);
    shaderProg.link();
    std::cout << vertFileName << " + " << fragFileName << " = " << shaderProg.getLinkStatus() << " " << shaderProg.getInfoLog() << std::endl;

    return shaderProg;
}
