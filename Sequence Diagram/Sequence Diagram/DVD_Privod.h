#pragma once

#include "Disk.h"

class DVD_Privod
{
public:
	Disk* disk = nullptr;
	bool open(Disk&);
};