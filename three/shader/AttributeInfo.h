#pragma once

#include <string>

namespace three {

struct AttributeInfo {
    std::string name;
    unsigned int dataType;
    int location = -1;
};

}
