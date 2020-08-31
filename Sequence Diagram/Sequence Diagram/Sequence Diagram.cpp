#include <iostream>

#include "DVD_Privod.h"
#include "Disk.h"


int main()
{
	DVD_Privod privod;
	std::string data = "Data";
	
	do {
		//std::cout << "\n Enter virtual disk path";
		std::string virtual_disk_path = "file.txt";
		//std::cin >> virtual_disk_path;

		Disk virtual_disk(virtual_disk_path);
		
	} while (not privod.open(virtual_disk));

}
