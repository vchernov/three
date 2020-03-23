#pragma once

#include <string>

#include "FileNotFoundException.h"

class FileSystem
{
public:
    static std::string readFile(const std::string& fn);
    static char* readBinaryFile(const std::string& fn);

    static std::string getFilePath(const std::string& fn);

    static std::string getCurrentDirectory();
    static void setCurrentDirectory(const std::string& path);
};
