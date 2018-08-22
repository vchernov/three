#pragma once

#include "ShaderProgram.h"

namespace three
{

class ShaderManager
{
public:
    virtual ~ShaderManager() = default;

    void setActive(const ShaderProgram* program);
    bool isActive(const ShaderProgram* program) const;

private:
    GLuint activeProgramHandle = 0;
};

}
