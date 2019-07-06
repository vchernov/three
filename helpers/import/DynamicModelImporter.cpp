#include "DynamicModelImporter.h"

#include <iostream>

#include "assimpHelpers.h"

class AssimpIntermediateImportResult : public DynamicModelImporter::IntermediateImportResult
{
public:
    Assimp::Importer importer;
    const aiScene* scene;

    AssimpIntermediateImportResult()
    {
        std::cout << "Intermediate import result created" << std::endl;
    }

    ~AssimpIntermediateImportResult()
    {
        std::cout << "Intermediate import result destroyed" << std::endl;
    }
};

std::shared_ptr<DynamicModelImporter::IntermediateImportResult> DynamicModelImporter::importModel(const std::string& fn)
{
    AssimpIntermediateImportResult* result = new AssimpIntermediateImportResult();
    result->scene = result->importer.ReadFile(fn.c_str(), aiProcess_Triangulate);
    return std::shared_ptr<AssimpIntermediateImportResult>(result);
}

Model DynamicModelImporter::loadModel(std::shared_ptr<DynamicModelImporter::IntermediateImportResult> intermediateResult)
{
    AssimpIntermediateImportResult* result = dynamic_cast<AssimpIntermediateImportResult*>(intermediateResult.get());
    return loadScene(result->scene);
}
