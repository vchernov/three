#pragma once

#include "GeometryBuffer.h"

class Shape {
public:
    static GeometryBuffer createCube();

    static GeometryBuffer createSphere(int slices, int stacks);
};
