#pragma once

#include "DVD_Reader.h"
#include "DVD_Writer.h"

#include "Disk.h"


class DVD_Drive
{
protected:
	DVD_Reader* reader = nullptr;
	DVD_Writer* writer = nullptr;

	unsigned    hash   = 0;

public:
	Disk*       disk   = nullptr;
	
	bool open(Disk&);
	bool verification(unsigned);

	bool read();
	bool write();
};
