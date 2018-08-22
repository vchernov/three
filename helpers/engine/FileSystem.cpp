#include "FileSystem.h"

#include <fstream>

std::string FileSystem::readFile(const std::string& fn)
{
    std::ifstream f(fn);
    return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
}
