#include "ChangeDir.h"

ChangeDir::ChangeDir(const std::string& dir)
{
    dirBefore = std::filesystem::current_path();
    std::filesystem::current_path(dir);
}

ChangeDir::~ChangeDir()
{
    std::filesystem::current_path(dirBefore);
}
