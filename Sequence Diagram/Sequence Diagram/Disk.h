#pragma once
#include <string>

class Disk
{
public:
	Disk() = default;
	Disk(std::string&);

	std::string data;
};

