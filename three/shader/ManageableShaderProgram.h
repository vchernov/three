#pragma once

#include "ShaderProgram.h"
#include "IDeferredUniform.h"

#include <memory>
#include <list>

namespace three
{

class ShaderManager;

class ManageableShaderProgram : public ShaderProgram
{
public:
    explicit ManageableShaderProgram(std::shared_ptr<ShaderManager> manager);

    void use() override;
    bool isActive() const;

protected:
    std::shared_ptr<ShaderManager> manager;
    std::list<std::shared_ptr<IDeferredUniform>> uniforms;
};

}
