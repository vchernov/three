#include "MeshBuilder.h"

#include "../../three/TypeInfo.h"

#include "Vertex.h"
#include "Face3.h"
#include "AttributeName.h"

template<>
void MeshBuilder::addAttributes<VertexPositionColor>(three::VertexBuffer& vertexBuffer) {
    vertexBuffer.addAttribute<glm::vec3>(AttributeName::position, offsetof(VertexPositionColor, position));
    vertexBuffer.addAttribute<glm::vec3>(AttributeName::color, offsetof(VertexPositionColor, color));
}

template<>
void MeshBuilder::addAttributes<VertexPositionTexture>(three::VertexBuffer& vertexBuffer) {
    vertexBuffer.addAttribute<glm::vec3>(AttributeName::position, offsetof(VertexPositionTexture, position));
    vertexBuffer.addAttribute<glm::vec2>(AttributeName::texCoord, offsetof(VertexPositionTexture, texCoord));
}

template<>
void MeshBuilder::uploadFaces<Face3>(three::IndexBuffer& indexBuffer, const std::vector<Face3>& faces) {
    indexBuffer.upload(faces.data(), three::TypeInfo<Face3::ValueType>::dataType, sizeof(Face3::ValueType), Face3::getIndexCount() * faces.size());
}
