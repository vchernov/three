#pragma once

#include <string>

namespace three {

struct VertexAttribute {
    VertexAttribute(
        std::string name,
        unsigned int dataType,
        int size,
        int offset,
        bool normalize = false)
        :
        name(std::move(name)),
        dataType(dataType),
        size(size),
        offset(offset),
        normalize(normalize) {
    }

    const std::string name;
    const unsigned int dataType;
    const int size;
    const int offset;
    const bool normalize;
};

}
