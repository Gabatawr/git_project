#include "Disk.h"
#include <fstream>
#include <iostream>

bool Disk::recover_data(std::string& file_name)
{
	std::ifstream file(file_name);
	
	if (file.is_open())
	{
		data.clear();
		data.reserve(disk_size);
		
		std::getline(file, data);
		if (data.size() > disk_size) data.resize(disk_size);
		
		data_size = data.size();
		
		return true;
	}
	return false;
}

     Disk::Disk       (std::string& file_name) { readable = recover_data(file_name); }
void Disk::operator() (std::string& file_name) { readable = recover_data(file_name); }

bool Disk::empty()   const { return data.empty(); }
bool Disk::is_open() const { return readable; }
