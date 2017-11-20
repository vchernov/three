#pragma once

#include <string>
#include <list>

#include "GeometryBuffer.h"
#include "BoundingBox.h"

class ModelLoader {
public:
    static std::list<GeometryBuffer> load(const std::string& fn, BoundingBox& bounds);
};
