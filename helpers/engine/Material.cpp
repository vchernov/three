#include "Material.h"

#include "UniformName.h"

void Material::applyShader(std::shared_ptr<three::SmartShaderProgram> shader)
{
    this->shader = std::move(shader);
    modelMatrixUniform = this->shader->getUniform<glm::mat4>(UniformName::modelMatrix);
}
