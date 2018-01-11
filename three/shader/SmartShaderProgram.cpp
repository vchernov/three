#include "SmartShaderProgram.h"

#include "ShaderManager.h"

namespace three {

SmartShaderProgram::SmartShaderProgram(std::shared_ptr<ShaderManager> manager)
    :
    manager(std::move(manager)) {
}

void SmartShaderProgram::use() {
    if (isActive()) {
        return;
    }
    ShaderProgram::use();
    manager->setActive(this);
    for (auto& uniform : uniforms) {
        uniform->apply();
    }
}

bool SmartShaderProgram::isActive() const {
    return manager->isActive(this);
}

}
