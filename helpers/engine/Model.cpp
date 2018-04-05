#include "Model.h"

void Model::draw() const {
    for (const auto& submesh : meshes) {
        submesh.getMesh().draw();
    }
}
