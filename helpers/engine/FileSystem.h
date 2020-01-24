#pragma once

#include <string>

#include "FileNotFoundException.h"

class FileSystem
{
public:
    static std::string readFile(const std::string& fn);
	static std::string getCurrentDirectory();
};
