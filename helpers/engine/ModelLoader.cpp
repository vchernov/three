#include "ModelLoader.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../three/TypeInfo.h"

#include "AttributeSemantic.h"

using namespace three;

Mesh loadMesh(const aiMesh* mesh, const IAttributeLocationBindings* locationBindings) {
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
    if (locationBindings->hasAttribute(AttributeSemantic::position)) {
        attributeBindings.attributes.push_back(VertexAttribute::create<float>(locationBindings->getAttributeInfo(AttributeSemantic::position).location, 3, 0, sizeof(aiVector3D)));
    }

    if (mesh->HasNormals()) {
        VertexBuffer::upload(positionsLength, normalsLength, mesh->mNormals);
        if (locationBindings->hasAttribute(AttributeSemantic::normal)) {
            attributeBindings.attributes.push_back(VertexAttribute::create<float>(locationBindings->getAttributeInfo(AttributeSemantic::normal).location, 3, positionsLength, sizeof(aiVector3D)));
        }
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

void extendBounds(const aiMesh* mesh, glm::vec3& lower, glm::vec3& upper) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        const aiVector3D& vert = mesh->mVertices[i];
        lower.x = fmin(vert.x, lower.x);
        lower.y = fmin(vert.y, lower.y);
        lower.z = fmin(vert.z, lower.z);
        upper.x = fmax(vert.x, upper.x);
        upper.y = fmax(vert.y, upper.y);
        upper.z = fmax(vert.z, upper.z);
    }
}

std::vector<Mesh> ModelLoader::load(const std::string& fn, const IAttributeLocationBindings* locationBindings, BoundingBox& bounds) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fn.c_str(), aiProcess_Triangulate);
    if (scene == nullptr) {
        std::cerr << importer.GetErrorString() << std::endl;
        throw std::runtime_error(importer.GetErrorString());
    }

    glm::vec3 lower = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 upper = glm::vec3(-std::numeric_limits<float>::max());

    std::vector<Mesh> meshes;
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(loadMesh(mesh, locationBindings));
        extendBounds(mesh, lower, upper);
    }

    bounds.size = upper - lower;
    bounds.center = lower + bounds.size * 0.5f;

    return meshes;
}
