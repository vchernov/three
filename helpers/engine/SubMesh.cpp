#include "SubMesh.h"

#include "UniformName.h"

SubMesh::SubMesh(three::Mesh mesh, std::shared_ptr<three::SmartShaderProgram> shader)
    :
    mesh(std::move(mesh)),
    shader(std::move(shader)) {
    modelMatrixUniform = this->shader->getUniform<glm::mat4>(UniformName::modelMatrix);
}
