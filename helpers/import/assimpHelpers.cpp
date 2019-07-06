#include "assimpHelpers.h"

#include <cassert>

#include "../../three/TypeInfo.h"

#include "../engine/AttributeLocation.h"

using namespace three;

Mesh loadMesh(const aiMesh* mesh)
{
    assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);

    AttributeBindings attributeBindings;
    VertexBuffer vertexBuffer;
    vertexBuffer.bind();

    int positionsLength = mesh->mNumVertices * sizeof(aiVector3D);
    int normalsLength = 0;
    if (mesh->HasNormals())
    {
        normalsLength = mesh->mNumVertices * sizeof(aiVector3D);
    }
    VertexBuffer::allocate(positionsLength + normalsLength);

    VertexBuffer::upload(0, positionsLength, mesh->mVertices);
    attributeBindings.attributes.push_back(VertexAttribute::create<float>(
        static_cast<int>(AttributeLocation::position),
        3, 0, sizeof(aiVector3D)));

    if (mesh->HasNormals())
    {
        VertexBuffer::upload(positionsLength, normalsLength, mesh->mNormals);
        attributeBindings.attributes.push_back(VertexAttribute::create<float>(
            static_cast<int>(AttributeLocation::normal),
            3,
            positionsLength,
            sizeof(aiVector3D)));
    }

    VertexBuffer::unbind();

    IndexBuffer indexBuffer;
    if (mesh->HasFaces())
    {
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        indexBuffer.bind();
        indexBuffer.allocate(
            TypeInfo<unsigned int>::dataType,
            sizeof(unsigned int),
            indices.size(),
            indices.data());
        IndexBuffer::unbind();
    }

    return Mesh::create(vertexBuffer, attributeBindings, std::move(indexBuffer), GL_TRIANGLES);
}

Model loadScene(const aiScene* scene)
{
    Model model;

    if (scene == nullptr)
    {
        return model;
    }

    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++)
    {
        const aiMesh* mesh = scene->mMeshes[mi];

        SubMesh submesh(loadMesh(mesh));

        for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++)
        {
            const aiVector3D& position = mesh->mVertices[vi];
            submesh.bounds.encapsulate(position.x, position.y, position.z);
        }

        model.meshes.push_back(std::move(submesh));
    }

    return model;
}
