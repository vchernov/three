#include "FileSystem.h"

#include <filesystem>
#include <fstream>

std::string FileSystem::readFile(const std::string& fn)
{
    std::ifstream f(fn);
    if (!f.is_open())
        throw FileNotFoundException(fn);
    return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
}

char* FileSystem::readBinaryFile(const std::string& fn)
{
    std::ifstream f(fn, std::ios::in | std::ios::binary | std::ios::ate);
    if (!f.is_open())
        throw FileNotFoundException(fn);

    size_t size = f.tellg();
    f.seekg(0, std::ios::beg);
    char* buffer = new char[size];
    f.read(buffer, size);
    f.close();

    return buffer;
}

std::string FileSystem::getFilePath(const std::string& fn)
{
    return std::filesystem::path(fn).parent_path().string();
}

std::string FileSystem::getCurrentDirectory()
{
    return std::filesystem::current_path().string();
}

void FileSystem::setCurrentDirectory(const std::string& path)
{
    std::filesystem::current_path(path);
}
