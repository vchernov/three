#include "ModelImporter.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "../engine/FileSystem.h"
#include "../engine/FileNotFoundException.h"

using namespace three;

ModelImporter::ModelData::ModelData(ModelGeometry geo, ImageRGB diffuseMap)
    : geo(std::move(geo))
    , diffuseMap(std::move(diffuseMap))
{
}

template<typename VertexType>
void copyPosition(const aiVector3D& position, VertexType& vertex)
{
    vertex.position.x = position.x;
    vertex.position.y = position.y;
    vertex.position.z = position.z;
}

template<typename VertexType>
void copyNormal(const aiVector3D& normal, VertexType& vertex)
{
    vertex.normal.x = normal.x;
    vertex.normal.y = normal.y;
    vertex.normal.z = normal.z;
}

template<typename VertexType>
void copyTexCoord(const aiVector3D& texCoord, VertexType& vertex)
{
    vertex.texCoord.x = texCoord.x;
    vertex.texCoord.y = texCoord.y;
}

std::vector<ModelImporter::ModelData> ModelImporter::loadGeometry(const std::string& fn)
{
    std::vector<ModelData> importedData;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fn.c_str(), aiProcess_Triangulate);
    if (scene == nullptr)
    {
        std::cerr << importer.GetErrorString() << std::endl;
        return importedData;
    }

    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++)
    {
        const aiMesh* mesh = scene->mMeshes[mi];
        std::cout << "Importing mesh " << mi << ": " << mesh->mName.C_Str() << std::endl;

        assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);
        assert(mesh->HasFaces());
        assert(mesh->HasPositions());
        assert(mesh->HasNormals());

        assert(mesh->HasTextureCoords(0));
        assert(mesh->mNumUVComponents[0] == 2);

        ModelGeometry geo;
        geo.primitiveType = GL_TRIANGLES;

        for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++)
        {
            ModelGeometry::Vertex vertex;

            copyPosition(mesh->mVertices[vi], vertex);
            copyNormal(mesh->mNormals[vi], vertex);
            copyTexCoord(mesh->mTextureCoords[0][vi], vertex);

            geo.vertices.push_back(vertex);
        }

        for (unsigned int fi = 0; fi < mesh->mNumFaces; fi++)
        {
            const aiFace& aiFace = mesh->mFaces[fi];
            assert(aiFace.mNumIndices == IndexedTriangle::getIndexCount());
            IndexedTriangle face;
            for (unsigned int i = 0; i < aiFace.mNumIndices; i++)
            {
                face.indices[i] = aiFace.mIndices[i];
            }
            geo.faces.push_back(face);
        }

        std::string cd = FileSystem::getCurrentDirectory();
        std::string modelFilePath = FileSystem::getFilePath(fn);
        FileSystem::setCurrentDirectory(modelFilePath);

        const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        aiString texFileName;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &texFileName);

        try
        {
            ImageRGB tex = ImageUtils::loadImage(texFileName.C_Str());
            std::cout << "Loaded texture: " << texFileName.C_Str() << " " << tex.getWidth() << "x" << tex.getWidth() << std::endl;
            importedData.push_back(ModelData(geo, std::move(tex)));
        }
        catch (FileNotFoundException& e)
        {
            std::cerr << e.what() << std::endl;
            ImageRGB whiteTex = ImageUtils::createPlainColorImage(2, 2, 255, 255, 255);
            importedData.push_back(ModelData(geo, std::move(whiteTex)));
        }

        FileSystem::setCurrentDirectory(cd);
    }

    return importedData;
}
