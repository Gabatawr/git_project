#pragma once

#include <string>


class Disk
{
protected:
	std::string data;

	unsigned    disk_size = 1024;
	unsigned    data_size = 0;
	
	bool        readable  = false;
	
	bool recover_data(std::string&);
	
public:
	Disk() = default;
	
	Disk(std::string&);
	void operator () (std::string&);

	bool empty()   const;
	bool is_open() const;
};

