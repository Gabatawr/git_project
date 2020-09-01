#include <iostream>

#include "DVD_Drive.h"
#include "Disk.h"


int main()
{
	DVD_Drive drive;
	std::string data = "Data";

	std::string virtual_disk_path = "file.txt";
	Disk disk(virtual_disk_path);

	while (not drive.open(disk))
	{
		std::cout << "\n Enter virtual disk path (or exit) : ";
		std::cin >> virtual_disk_path;

		if (virtual_disk_path == "exit") return 0;
		disk(virtual_disk_path);
	}

	char choice; do {
		std::cout << "\n 1. Read disk data"
				  << "\n 2. Write new data"
				  << "\n 0. Exit"
				  << "\n _.\b\b";
		std::cin >> choice;
		if (choice == '0') return 0;
	} while (choice != '1' && choice != '2');
	
	if (choice == '1') drive.
	

}
