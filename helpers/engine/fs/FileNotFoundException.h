#pragma once

#include <stdexcept>

class FileNotFoundException : public std::runtime_error
{
public:
	FileNotFoundException(std::string fn) : std::runtime_error("File not found: " + fn)
	{
	}
};
