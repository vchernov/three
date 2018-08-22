#pragma once

#include <glm/glm.hpp>

#include "../../three/mesh/Mesh.h"

class Shape
{
public:
    static three::Mesh createTriangle();

    static three::Mesh createCube();

    static three::Mesh createGrid(glm::vec3 point0, glm::vec3 point1, glm::vec3 point2, int rows, int columns);

    static three::Mesh createSphere(int slices, int stacks);
};
