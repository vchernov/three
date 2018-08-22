#pragma once

#include "ManageableShaderProgram.h"
#include "SmartUniform.h"

#include <memory>
#include <list>

namespace three
{

class ShaderManager;

class SmartShaderProgram : public ManageableShaderProgram, public std::enable_shared_from_this<SmartShaderProgram>
{
public:
    explicit SmartShaderProgram(std::shared_ptr<ShaderManager> manager)
        :
        ManageableShaderProgram(std::move(manager))
    {
    }

    template<typename T>
    std::weak_ptr<SmartUniform<T>> getUniform(const std::string& name)
    {
        int location = getUniformLocation(name);
        auto uniform = std::make_shared<SmartUniform<T>>(location, shared_from_this());
        uniforms.push_back(uniform);
        return uniform;
    }
};

}
