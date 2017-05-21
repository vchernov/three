#pragma once

#include <string>

class FileSystem {
public:
    static std::string readFile(const std::string& fn);
};
