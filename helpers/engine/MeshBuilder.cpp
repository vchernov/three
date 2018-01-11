#include "MeshBuilder.h"

#include "../../three/TypeInfo.h"

#include "Vertex.h"
#include "Face3.h"

using namespace three;

template<>
std::vector<VertexAttribute> MeshBuilder::getAttributes<VertexPositionColor>(const IAttributeLocationBindings* locationBindings) {
    std::vector<VertexAttribute> attributes;
    attributes.push_back(VertexAttribute::create<glm::vec3>(locationBindings->getAttributeInfo(AttributeSemantic::position), 0, sizeof(VertexPositionColor)));
    attributes.push_back(VertexAttribute::create<glm::vec3>(locationBindings->getAttributeInfo(AttributeSemantic::color), sizeof(glm::vec3), sizeof(VertexPositionColor)));
    return attributes;
}

template<>
std::vector<VertexAttribute> MeshBuilder::getAttributes<VertexPositionTexture>(const IAttributeLocationBindings* locationBindings) {
    std::vector<VertexAttribute> attributes;
    attributes.push_back(VertexAttribute::create<glm::vec3>(locationBindings->getAttributeInfo(AttributeSemantic::position), 0, sizeof(VertexPositionTexture) ));
    attributes.push_back(VertexAttribute::create<glm::vec2>(locationBindings->getAttributeInfo(AttributeSemantic::texCoord), sizeof(glm::vec3), sizeof(VertexPositionTexture)));
    return attributes;
}

template<>
void MeshBuilder::uploadFaces<Face3>(IndexBuffer& indexBuffer, const std::vector<Face3>& faces) {
    indexBuffer.allocate(TypeInfo<Face3::ValueType>::dataType, sizeof(Face3::ValueType), Face3::getIndexCount() * faces.size(), faces.data());
}
