#pragma once

#include "ShaderProgram.h"
#include "SmartUniform.h"

#include <memory>
#include <list>

namespace three {

class ShaderManager;

class SmartShaderProgram : public ShaderProgram, public std::enable_shared_from_this<SmartShaderProgram> {
public:
    SmartShaderProgram(std::shared_ptr<ShaderManager> manager);
    virtual ~SmartShaderProgram() = default;

    void use() override;
    bool isActive() const;

    template<typename T>
    std::weak_ptr<SmartUniform<T>> getUniform(const std::string& name) {
        int location = getUniformLocation(name);
        auto uniform = std::make_shared<SmartUniform<T>>(location, shared_from_this());
        uniforms.push_back(uniform);
        return uniform;
    }

private:
    std::shared_ptr<ShaderManager> manager;
    std::list<std::shared_ptr<IDeferredUniform>> uniforms;
};

}
