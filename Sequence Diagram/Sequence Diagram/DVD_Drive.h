#pragma once

#include "Disk.h"


class DVD_Drive
{
public:
	Disk* disk = nullptr;
	
	bool open(Disk&);

	void read()                   const;
	bool write(std::string& data) const;
};