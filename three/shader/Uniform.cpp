#include "Uniform.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace three
{

template<>
void Uniform<float>::update(int location, float value)
{
    glUniform1f(location, value);
}

template<>
void Uniform<int>::update(int location, int value)
{
    glUniform1i(location, value);
}

template<>
void Uniform<glm::vec2>::update(int location, glm::vec2 value)
{
    glUniform2fv(location, 1, glm::value_ptr(value));
}

template<>
void Uniform<glm::vec3>::update(int location, glm::vec3 value)
{
    glUniform3fv(location, 1, glm::value_ptr(value));
}

template<>
void Uniform<glm::mat4>::update(int location, glm::mat4 value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

}
