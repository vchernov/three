#include "assimpHelpers.h"

#include "../engine/AttributeLocation.h"

using namespace three;

unsigned int* importTriangleIndices(const aiMesh* mesh)
{
    unsigned int* indices = new unsigned int[mesh->mNumFaces * 3];
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& aiFace = mesh->mFaces[i];
        //assert(aiFace.mNumIndices == 3);
        memcpy(indices + i * 3, aiFace.mIndices, sizeof(unsigned int) * 3);
    }
    return indices;
}

void uploadIndices(const aiMesh* mesh, unsigned int* triangleIndices, IndexBuffer& indexBuffer)
{
    if (!mesh->HasFaces())
        return;

    indexBuffer.bind();
    indexBuffer.allocate(
        TypeInfo<unsigned int>::dataType,
        sizeof(unsigned int),
        mesh->mNumFaces * 3,
        triangleIndices);
    IndexBuffer::unbind();
}

AttributeBindings uploadVertices(const aiMesh* mesh, VertexBuffer& vertexBuffer)
{
    AttributeBindings attributeBindings;
    vertexBuffer.bind();

    int positionsLength = mesh->mNumVertices * sizeof(aiVector3D);
    int normalsLength = 0;
    if (mesh->HasNormals())
        normalsLength = mesh->mNumVertices * sizeof(aiVector3D);
    VertexBuffer::allocate(positionsLength + normalsLength);

    VertexBuffer::upload(0, positionsLength, mesh->mVertices);
    attributeBindings.attributes.push_back(
        VertexAttribute::create<float>(static_cast<int>(AttributeLocation::position), 3, 0, sizeof(aiVector3D))
    );

    if (mesh->HasNormals())
    {
        VertexBuffer::upload(positionsLength, normalsLength, mesh->mNormals);
        attributeBindings.attributes.push_back(
            VertexAttribute::create<float>(static_cast<int>(AttributeLocation::normal), 3, positionsLength, sizeof(aiVector3D))
        );
    }

    VertexBuffer::unbind();
    return attributeBindings;
}
