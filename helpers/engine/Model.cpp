#include "Model.h"

void Model::draw() const {
    for (const auto& submesh : meshes) {
        submesh.shader->use();
        submesh.modelMatrixUniform.lock()->set(transform.getTransformationMatrix());
        submesh.mesh.draw();
    }
}
