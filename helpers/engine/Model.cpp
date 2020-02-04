#include "Model.h"

using namespace three;

void Model::draw() const
{
    for (const auto& submesh : meshes)
    {
        submesh.material.shader->use();
        submesh.material.diffuseTex.bind();
        submesh.material.modelMatrixUniform.lock()->set(transform.getTransformationMatrix());
        submesh.mesh.draw();
        Texture2D::unbind();
    }
}
