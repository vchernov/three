#pragma once

#include "../../three/shader/ShaderProgram.h"

class ShaderUtils {
public:
    static void loadShaderProgram(three::ShaderProgram* program, const std::string& vertFileName, const std::string& fragFileName);

    static three::ShaderProgram loadShaderProgram(const std::string& vertFileName, const std::string& fragFileName);
};
