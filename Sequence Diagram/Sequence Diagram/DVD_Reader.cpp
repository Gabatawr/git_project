#include "DVD_Reader.h"

#include <iostream>


void DVD_Reader::read(Disk* disk)
{
	std::cout << "\n " << disk->get_data();
}