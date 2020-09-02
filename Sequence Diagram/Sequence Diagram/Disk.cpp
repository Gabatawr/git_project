#include "Disk.h"
#include <fstream>
#include <iostream>


void Disk::clear_data()
{
	data.clear();
	data.reserve(disk_size);
}

bool Disk::recover_data(std::string& file_name)
{
	std::ifstream file(file_name);
	
	if (file.is_open())
	{
		clear_data();
		
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

std::string Disk::get_data()      const { return data; }

void Disk::set_data(std::string& data)
{
	this->data = data;
	this->data.reserve(disk_size);
}

unsigned Disk::get_disk_size() const { return disk_size; }

unsigned Disk::get_hash() const
{
	std::hash<std::string> encoder;
	return encoder(data);
}
