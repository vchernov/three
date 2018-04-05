#pragma once

#include <glm/glm.hpp>

struct VertexPositionColor {
    glm::vec3 position;
    glm::vec3 color;
};

struct VertexPositionTexture {
    glm::vec3 position;
    glm::vec2 texCoord;
};

struct VertexPositionColorTexture {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
};

struct VertexPositionNormal {
    glm::vec3 position;
    glm::vec3 normal;
};

struct VertexPositionNormalTexture {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};
