#include "ModelImporter.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace three;

std::vector<ModelImporter::ModelGeometry> ModelImporter::loadGeometry(const std::string& fn)
{
    std::vector<ModelGeometry> geometry;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fn.c_str(), aiProcess_Triangulate);
    if (scene == nullptr)
    {
        std::cerr << importer.GetErrorString() << std::endl;
        return geometry;
    }

    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++)
    {
        const aiMesh* mesh = scene->mMeshes[mi];
        assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);
        assert(mesh->HasFaces());
        assert(mesh->HasPositions());
        assert(mesh->HasNormals());

        ModelGeometry geo;
        geo.primitiveType = GL_TRIANGLES;

        for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++)
        {
            ModelGeometry::Vertex vertex;

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

        for (unsigned int fi = 0; fi < mesh->mNumFaces; fi++)
        {
            const aiFace& aiFace = mesh->mFaces[fi];
            assert(aiFace.mNumIndices == ModelImporter::Face::getIndexCount());
            ModelImporter::Face face;
            for (unsigned int i = 0; i < aiFace.mNumIndices; i++)
            {
                face.indices[i] = aiFace.mIndices[i];
            }
            geo.faces.push_back(face);
        }

        geometry.push_back(geo);
    }

    return geometry;
}
