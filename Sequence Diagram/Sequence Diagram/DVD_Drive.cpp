#include "DVD_Drive.h"

#include <iostream>


bool DVD_Drive::open(Disk& disk)
{
	if (disk.is_open())
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

bool DVD_Drive::verification(unsigned)
{
	
}

bool DVD_Drive::read()
{
	reader = new DVD_Reader;
	reader->read(disk);
}
