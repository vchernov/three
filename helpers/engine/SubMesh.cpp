#include "SubMesh.h"

#include "UniformName.h"

SubMesh::SubMesh(three::Mesh mesh)
    :
    mesh(std::move(mesh))
{
}

void SubMesh::applyShader(std::shared_ptr<three::SmartShaderProgram> shader)
{
    this->shader = std::move(shader);
    modelMatrixUniform = this->shader->getUniform<glm::mat4>(UniformName::modelMatrix);
}
