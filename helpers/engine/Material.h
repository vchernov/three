#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "../../three/shader/SmartShaderProgram.h"
#include "../../three/texture/Texture2D.h"

struct Material
{
    three::Texture2D diffuseTex;

    std::shared_ptr<three::SmartShaderProgram> shader;
    std::weak_ptr<three::SmartUniform<glm::mat4>> modelMatrixUniform;

    void applyShader(std::shared_ptr<three::SmartShaderProgram> shader);
};
