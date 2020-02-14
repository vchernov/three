#pragma once

#include <string>
#include <filesystem>

class ChangeDir
{
public:
    ChangeDir(const std::string& dir);
    virtual ~ChangeDir();

private:
    std::filesystem::path dirBefore;
};
