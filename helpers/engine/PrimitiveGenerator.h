#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "../../three/mesh/Mesh.h"

#include "IAttributeLocationBindings.h"

class PrimitiveGenerator {
public:
    explicit PrimitiveGenerator(std::shared_ptr<IAttributeLocationBindings> locationBindings);
    virtual ~PrimitiveGenerator() = default;

    three::Mesh createTriangle() const;

    three::Mesh createCube() const;

    three::Mesh createGrid(glm::vec3 point0, glm::vec3 point1, glm::vec3 point2, int rows, int columns) const;

    three::Mesh createSphere(int slices, int stacks) const;

private:
    std::shared_ptr<IAttributeLocationBindings> locationBindings;
};
