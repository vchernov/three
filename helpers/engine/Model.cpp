#include "Model.h"

using namespace three;

Model::Model(three::Mesh mesh)
    : mesh(std::move(mesh))
{
}

void Model::draw(glm::mat4 modelMatrix) const
{
    material.shader->use();
    material.diffuseTex.bind();
    material.modelMatrixUniform.lock()->set(modelMatrix);
    mesh.draw();
    Texture2D::unbind();
}
