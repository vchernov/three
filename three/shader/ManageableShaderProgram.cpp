#include "ManageableShaderProgram.h"

#include "ShaderManager.h"

namespace three
{

ManageableShaderProgram::ManageableShaderProgram(std::shared_ptr<ShaderManager> manager)
    :
    manager(std::move(manager))
{
}

void ManageableShaderProgram::use()
{
    if (isActive())
    {
        return;
    }
    ShaderProgram::use();
    manager->setActive(this);
    for (auto& uniform : uniforms)
    {
        uniform->apply();
    }
}

bool ManageableShaderProgram::isActive() const
{
    return manager->isActive(this);
}

}
