#pragma once

#include "../../three/shader/ShaderProgram.h"

class ShaderUtils {
public:
    static three::ShaderProgram loadShaderProgram(const std::string& vertFileName, const std::string& fragFileName);
};
