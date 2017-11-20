#include "ModelLoader.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../three/TypeInfo.h"

#include "AttributeName.h"

using namespace three;

GeometryBuffer loadMesh(const aiMesh* mesh) {
    assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);

    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    if (mesh->HasPositions()) {
        VertexBuffer pointBuffer;
        pointBuffer.bind();
        pointBuffer.upload(mesh->mVertices, mesh->mNumVertices, sizeof(aiVector3D));
        pointBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
        geometry.vertexBuffers.push_back(std::move(pointBuffer));
    }

    if (mesh->HasNormals()) {
        VertexBuffer normalBuffer;
        normalBuffer.bind();
        normalBuffer.upload(mesh->mNormals, mesh->mNumVertices, sizeof(aiVector3D));
        normalBuffer.addAttribute({AttributeName::normal, TypeInfo<float>::dataType, 3, 0});
    }

    if (mesh->HasFaces()) {
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        geometry.indexBuffer.bind();
        geometry.indexBuffer.upload(indices.data(), TypeInfo<unsigned int>::dataType, sizeof(unsigned int), indices.size());
    }

    return geometry;
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

std::list<GeometryBuffer> ModelLoader::load(const std::string& fn, BoundingBox& bounds) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fn.c_str(), aiProcess_Triangulate);
    if (scene == nullptr) {
        std::cerr << importer.GetErrorString() << std::endl;
        throw std::runtime_error(importer.GetErrorString());
    }

    std::list<GeometryBuffer> geos;

    glm::vec3 lower = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 upper = glm::vec3(-std::numeric_limits<float>::max());

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        geos.push_back(loadMesh(mesh));
        extendBounds(mesh, lower, upper);
    }

    bounds.size = upper - lower;
    bounds.center = lower + bounds.size * 0.5f;

    return geos;
}
