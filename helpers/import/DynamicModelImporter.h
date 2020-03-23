#pragma once

#include <string>
#include <memory>

#include "../engine/scene/Node.h"

class DynamicModelImporter
{
public:
    class IntermediateImportResult
    {
    public:
        virtual ~IntermediateImportResult() = default;
    };

    static std::shared_ptr<IntermediateImportResult> importModel(const std::string& fn);
    static Node loadModel(std::shared_ptr<IntermediateImportResult> intermediateResult);
};
