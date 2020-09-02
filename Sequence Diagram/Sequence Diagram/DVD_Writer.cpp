#include "DVD_Writer.h"

#include <iostream>


bool DVD_Writer::write(Disk* disk, std::string& data, unsigned& hash)
{
	if (data.size() > disk->get_disk_size())
	{
		std::cout << "\n Insufficient space to write data";
		return false;
	}
	
	disk->set_data(data);
	hash = disk->get_hash();
	
	return true;
}