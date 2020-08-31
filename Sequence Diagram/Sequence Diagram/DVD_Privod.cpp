#include "DVD_Privod.h"

#include <iostream>


bool DVD_Privod::open(Disk& disk)
{
	if (disk.data.empty())
	{
		std::cout << "Disk not open";
		return false;
	}
	else
	{
		std::cout << "Disk opened";
		this->disk = &disk;
		return true;
	}
}
