#include "ModelLoader.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../three/TypeInfo.h"

#include "../engine/AttributeLocation.h"

using namespace three;

std::vector<ModelLoader::Geometry> ModelLoader::loadGeometry(const std::string& fn) {
    std::vector<Geometry> geometry;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fn.c_str(), aiProcess_Triangulate);
    if (scene == nullptr) {
        std::cerr << importer.GetErrorString() << std::endl;
        return geometry;
    }

    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++) {
        const aiMesh* mesh = scene->mMeshes[mi];
        assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);
        assert(mesh->HasFaces());
        assert(mesh->HasPositions());
        assert(mesh->HasNormals());

        Geometry geo;
        geo.primitiveType = GL_TRIANGLES;

        for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++) {
            Geometry::Vertex vertex;

            const aiVector3D& position = mesh->mVertices[vi];
            vertex.position.x = position.x;
            vertex.position.y = position.y;
            vertex.position.z = position.z;

            const aiVector3D& normal = mesh->mNormals[vi];
            vertex.normal.x = normal.x;
            vertex.normal.y = normal.y;
            vertex.normal.z = normal.z;

            geo.vertices.push_back(vertex);
        }

        for (unsigned int fi = 0; fi < mesh->mNumFaces; fi++) {
            const aiFace& face = mesh->mFaces[fi];
            Geometry::Face geoFace;
            for (auto i = 0; i < Geometry::Face::getIndexCount(); i++) {
                geoFace.indices[i] = face.mIndices[i];
            }
            geo.faces.push_back(geoFace);
        }

        geometry.push_back(geo);
    }

    return geometry;
}

Mesh loadMesh(const aiMesh* mesh) {
    assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);

    AttributeBindings attributeBindings;
    VertexBuffer vertexBuffer;
    vertexBuffer.bind();

    int positionsLength = mesh->mNumVertices * sizeof(aiVector3D);
    int normalsLength = 0;
    if (mesh->HasNormals()) {
        normalsLength = mesh->mNumVertices * sizeof(aiVector3D);
    }
    VertexBuffer::allocate(positionsLength + normalsLength);

    VertexBuffer::upload(0, positionsLength, mesh->mVertices);
    attributeBindings.attributes.push_back(VertexAttribute::create<float>(static_cast<int>(AttributeLocation::position), 3, 0, sizeof(aiVector3D)));

    if (mesh->HasNormals()) {
        VertexBuffer::upload(positionsLength, normalsLength, mesh->mNormals);
        attributeBindings.attributes.push_back(VertexAttribute::create<float>(static_cast<int>(AttributeLocation::normal), 3, positionsLength, sizeof(aiVector3D)));
    }

    VertexBuffer::unbind();

    IndexBuffer indexBuffer;
    if (mesh->HasFaces()) {
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        indexBuffer.bind();
        indexBuffer.allocate(TypeInfo<unsigned int>::dataType, sizeof(unsigned int), indices.size(), indices.data());
        IndexBuffer::unbind();
    }

    return Mesh::create(vertexBuffer, attributeBindings, std::move(indexBuffer), GL_TRIANGLES);
}

Model loadModel(const aiScene* scene) {
    Model model;

    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++) {
        const aiMesh* mesh = scene->mMeshes[mi];
        
        BoundingBox bounds;
        for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++) {
            const aiVector3D& position = mesh->mVertices[vi];
            bounds.encapsulate(position.x, position.y, position.z);
        }
    }

    return model;
}
