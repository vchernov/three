#pragma once

#include <GL/glew.h>

namespace three {

template<typename T>
struct TypeInfo {
    static const GLenum dataType;
};

}
