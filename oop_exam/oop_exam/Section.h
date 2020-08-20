#pragma once
#include "Test.h"
#include "Stat_section.h"

#include <map>

#include <string>
using std::string;


class Section : public Stat_section
{
protected: 

public:    std::map <string, Test*> tests;
	
	       void add_test();
		   bool save(std::ofstream&);
		   bool load(std::ifstream&);
private:   
};