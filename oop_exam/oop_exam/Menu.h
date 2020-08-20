#pragma once
#include "Tesys.h"
#include "User.h"

using std::hash;

#include <string>
using std::string;


class Menu
{
protected: Tesys        tesys;
		   User*        user = nullptr;

		   string       login,
		                password,
		                name,
		                email,
		                phone;

		   hash<string> encrypt;
		   unsigned     e_login = 0,
	                    e_password = 0;
	
		   void enter_login();
		   void enter_password();
		   void enter_optional();
	
		   void sign_up(bool = false);
		   void sign_in();
	
		   void menu_login();
		   void menu_stat();
	
		   void menu_one();

public:    Menu() = default;
		  ~Menu() = default;
	
  explicit Menu(string);      // load
           void save(string); // save
	
		   void loop();
	
	static char choice;
	static void enter_choice(bool = false);
	static bool ask_yn(const char*);
	
private:
};

