#include "DVD_Drive.h"

#include "DVD_Reader.h"
#include "DVD_Writer.h"

#include <iostream>


bool DVD_Drive::open(Disk& disk)
{
	if (not disk.is_open())
	{
		std::cout << "\n Disk not open";
		this->disk = nullptr;
		return false;
	}
	else
	{
		std::cout << "\n Disk opened";
		if (disk.empty()) std::cout << "\n Disk is empty";
		
		this->disk = &disk;
		return true;
	}
}

void DVD_Drive::read() const
{
	DVD_Reader reader;
	reader.read(disk);
}

bool DVD_Drive::write(std::string& data) const
{
	DVD_Writer writer;
	
	std::hash<std::string> encoder;
	unsigned hash_one = encoder(data), hash_two;
	
	if (not writer.write(disk, data, hash_two))
	{
		std::cout << "\n Error writing data to disk";
		return false;
	}
	
	if (hash_one != hash_two)
	{
		std::cout << "\n Data verification error";
		return false;
	}

	std::cout << "\n Data written to disk";
	return true;
}
