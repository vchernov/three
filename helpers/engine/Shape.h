#pragma once

#include "GeometryBuffer.h"

#include <glm/glm.hpp>

class Shape {
public:
    static GeometryBuffer createTriangle();

    static GeometryBuffer createGrid(glm::vec3 point0, glm::vec3 point1, glm::vec3 point2, int rows, int columns);

    static GeometryBuffer createCube();

    static GeometryBuffer createSphere(int slices, int stacks);
};
