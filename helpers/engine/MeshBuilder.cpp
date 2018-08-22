#include "MeshBuilder.h"

#include "Vertex.h"
#include "AttributeLocation.h"

using namespace three;

template<>
AttributeBindings MeshBuilder::getAttributes<VertexPositionColor>()
{
    AttributeBindings bindings;
    bindings.attributes.push_back(VertexAttribute::create<glm::vec3>(
        static_cast<int>(AttributeLocation::position), 0, sizeof(VertexPositionColor)));
    bindings.attributes.push_back(VertexAttribute::create<glm::vec3>(
        static_cast<int>(AttributeLocation::color), sizeof(glm::vec3), sizeof(VertexPositionColor)));
    return bindings;
}

template<>
AttributeBindings MeshBuilder::getAttributes<VertexPositionTexture>()
{
    AttributeBindings bindings;
    bindings.attributes.push_back(VertexAttribute::create<glm::vec3>(
        static_cast<int>(AttributeLocation::position), 0, sizeof(VertexPositionTexture)));
    bindings.attributes.push_back(VertexAttribute::create<glm::vec2>(
        static_cast<int>(AttributeLocation::texCoord), sizeof(glm::vec3), sizeof(VertexPositionTexture)));
    return bindings;
}

template<>
AttributeBindings MeshBuilder::getAttributes<VertexPositionNormal>()
{
    AttributeBindings bindings;
    bindings.attributes.push_back(VertexAttribute::create<glm::vec3>(
        static_cast<int>(AttributeLocation::position), 0, sizeof(VertexPositionNormal)));
    bindings.attributes.push_back(VertexAttribute::create<glm::vec3>(
        static_cast<int>(AttributeLocation::normal), sizeof(glm::vec3), sizeof(VertexPositionNormal)));
    return bindings;
}
