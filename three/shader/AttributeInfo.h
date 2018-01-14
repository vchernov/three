#pragma once

#include <string>

#include <GL/glew.h>

namespace three {

struct AttributeInfo {
    std::string name;
    GLenum dataType;
    int location = -1;
};

}
