#include "FileSystem.h"

#include <fstream>
#include <filesystem>

std::string FileSystem::readFile(const std::string& fn)
{
    std::ifstream f(fn);
	if (!f.is_open())
		throw FileNotFoundException(fn);
    return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
}

std::string FileSystem::getCurrentDirectory()
{
	return std::filesystem::current_path().string();
}
