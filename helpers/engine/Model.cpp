#include "Model.h"

void Model::draw() const {
    for (const auto& mesh : meshes) {
        mesh.draw();
    }
}
