#pragma once

#include "Disk.h"


class DVD_Writer
{
public:
	bool write(Disk*, std::string&, unsigned&);
};