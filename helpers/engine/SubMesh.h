#pragma once

#include <memory>

#include "../../three/mesh/Mesh.h"
#include "../../three/shader/SmartShaderProgram.h"

#include "BoundingBox.h"

struct SubMesh final
{
    three::Mesh mesh;
    BoundingBox bounds;
    std::shared_ptr<three::SmartShaderProgram> shader;
    std::weak_ptr<three::SmartUniform<glm::mat4>> modelMatrixUniform;

    SubMesh(three::Mesh mesh, std::shared_ptr<three::SmartShaderProgram> shader);
};
