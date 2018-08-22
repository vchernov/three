#include "ShaderManager.h"

namespace three
{

void ShaderManager::setActive(const ShaderProgram* program)
{
    activeProgramHandle = program->getHandle();
}

bool ShaderManager::isActive(const ShaderProgram* program) const
{
    return program->getHandle() == activeProgramHandle;
}

}
