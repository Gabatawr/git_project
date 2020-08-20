#pragma once
#include "Stat.h"
#include "Stat_user_test.h"

#include <list>

#include <string>
using std::string;


class Stat_user : public Stat
{
protected: 

public:    std::list<Stat_user_test*> user_test_list;
	
	       void show_stat_sections(string);
		   void show_stat_tests();

private:
};