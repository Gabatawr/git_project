#pragma once
#include "User.h"
#include "Section.h"

#include <map>

#include <iostream>
using std::cin;
using std::cout;

#include <string>
using std::string;


class Tesys
{
protected: 

public:    std::map <unsigned, User*>  users;
	       std::map <string, Section*> sections;

		   Tesys() = default;
		  ~Tesys() = default;
	
  explicit Tesys(string&);            // load
		   bool save(std::ofstream&); // save
		  
		   bool check_admin();
		   User* try_login(unsigned, unsigned);

		   void add_section();

private:
};

