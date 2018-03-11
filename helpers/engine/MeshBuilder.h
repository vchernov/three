#pragma once

#include "../../three/mesh/Mesh.h"
#include "../../three/mesh/AttributeBindings.h"

#include "Geometry.h"

class MeshBuilder {
public:
    template<typename VertexType, typename FaceType>
    static three::Mesh build(const Geometry<VertexType, FaceType>& geometry) {
        three::VertexBuffer vertexBuffer;
        vertexBuffer.bind();
        three::VertexBuffer::allocate(geometry.vertices);

        three::IndexBuffer indexBuffer;
        indexBuffer.bind();
        uploadFaces<FaceType>(indexBuffer, geometry.faces);

        return three::Mesh::create(vertexBuffer, getAttributes<VertexType>(), std::move(indexBuffer), geometry.primitiveType);
    }

private:
    template<typename VertexType>
    static three::AttributeBindings getAttributes();

    template<typename FaceType>
    static void uploadFaces(three::IndexBuffer& indexBuffer, const std::vector<FaceType>& faces);
};
