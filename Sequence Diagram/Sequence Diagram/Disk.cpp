#include "Disk.h"
#include <fstream>

Disk::Disk(std::string& file_name)
{
	std::ifstream file(file_name);
	if (file.is_open()) file >> data;
}