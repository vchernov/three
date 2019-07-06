#pragma once

#include <string>
#include <memory>

#include "../engine/Model.h"

class DynamicModelImporter
{
public:
    class IntermediateImportResult
    {
    public:
        virtual ~IntermediateImportResult() = default;
    };

    static std::shared_ptr<IntermediateImportResult> importModel(const std::string& fn);
    static Model loadModel(std::shared_ptr<IntermediateImportResult> intermediateResult);
};
