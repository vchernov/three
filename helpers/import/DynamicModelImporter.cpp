#include "DynamicModelImporter.h"

#include <iostream>

#include "assimpHelpers.h"

using namespace three;

class AssimpIntermediateImportResult : public DynamicModelImporter::IntermediateImportResult
{
public:
    Assimp::Importer importer;
    const aiScene* scene = nullptr;
    std::vector<unsigned int*> allIndices;
    std::vector<BoundingBox> allBounds;

    AssimpIntermediateImportResult()
    {
        std::cout << "Intermediate import result created" << std::endl;
    }

    ~AssimpIntermediateImportResult()
    {
        for (unsigned int i = 0; i < allIndices.size(); i++)
            delete[] allIndices[i];

        std::cout << "Intermediate import result destroyed" << std::endl;
    }
};

std::vector<unsigned int*> importAllIndices(const aiScene* scene)
{
    std::vector<unsigned int*> allIndices;
    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++)
    {
        const aiMesh* mesh = scene->mMeshes[mi];
        allIndices.push_back(importTriangleIndices(mesh));
    }
    return allIndices;
}

std::vector<BoundingBox> importAllBounds(const aiScene* scene)
{
    std::vector<BoundingBox> allBounds;
    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++)
    {
        const aiMesh* mesh = scene->mMeshes[mi];
        BoundingBox bounds;
        for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++)
        {
            const aiVector3D& position = mesh->mVertices[vi];
            bounds.encapsulate(position.x, position.y, position.z);
        }
        allBounds.push_back(bounds);
    }
    return allBounds;
}

Mesh loadMesh(const aiMesh* mesh, unsigned int* cachedIndices)
{
    assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);
    
    VertexBuffer vertexBuffer;
    AttributeBindings attributeBindings = uploadVertices(mesh, vertexBuffer);

    IndexBuffer indexBuffer;
    uploadIndices(mesh, cachedIndices, indexBuffer);

    return Mesh::create(vertexBuffer, attributeBindings, std::move(indexBuffer), GL_TRIANGLES);
}

Model loadScene(const aiScene* scene, const std::vector<unsigned int*>& allIndices, const std::vector<BoundingBox>& allBounds)
{
    Model model;

    if (scene == nullptr)
    {
        return model;
    }

    for (unsigned int mi = 0; mi < scene->mNumMeshes; mi++)
    {
        const aiMesh* mesh = scene->mMeshes[mi];
        SubMesh submesh(loadMesh(mesh, allIndices[mi]));
        submesh.bounds = allBounds[mi];
        model.meshes.push_back(std::move(submesh));
    }

    return model;
}

std::shared_ptr<DynamicModelImporter::IntermediateImportResult> DynamicModelImporter::importModel(const std::string& fn)
{
    AssimpIntermediateImportResult* result = new AssimpIntermediateImportResult();
    result->scene = result->importer.ReadFile(fn.c_str(), aiProcess_Triangulate);
    result->allIndices = importAllIndices(result->scene);
    result->allBounds = importAllBounds(result->scene);
    return std::shared_ptr<AssimpIntermediateImportResult>(result);
}

Model DynamicModelImporter::loadModel(std::shared_ptr<DynamicModelImporter::IntermediateImportResult> intermediateResult)
{
    AssimpIntermediateImportResult* result = dynamic_cast<AssimpIntermediateImportResult*>(intermediateResult.get());
    return loadScene(result->scene, result->allIndices, result->allBounds);
}
