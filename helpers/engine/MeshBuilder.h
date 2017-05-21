#pragma once

#include "../../three/mesh/Mesh.h"

#include "Geometry.h"

class MeshBuilder {
public:
    template<typename VertexType, typename FaceType>
    static three::Mesh build(const Geometry<VertexType, FaceType>& geometry, const three::ShaderProgram& shaderProg) {
        three::VertexBuffer vertexBuffer;
        vertexBuffer.bind();
        vertexBuffer.upload(geometry.vertices);
        addAttributes<VertexType>(vertexBuffer);

        three::IndexBuffer indexBuffer;
        indexBuffer.bind();
        uploadFaces<FaceType>(indexBuffer, geometry.faces);

        return three::Mesh::create(vertexBuffer, std::move(indexBuffer), shaderProg, geometry.primitiveType);
    }

private:
    template<typename VertexType>
    static void addAttributes(three::VertexBuffer& vertexBuffer);

    template<typename FaceType>
    static void uploadFaces(three::IndexBuffer& indexBuffer, const std::vector<FaceType>& faces);
};
