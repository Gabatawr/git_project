#pragma once
#include "Stat_user.h"

#include <string>
using std::string;

class User : public Stat_user
{
protected: unsigned login;
		   unsigned password;

		   string   name;
		   string   email;
		   string   phone;
	
		   bool     is_admin;
	
public:    User(bool, unsigned&, unsigned&, string = "unknown", string = "unknown", string = "unknown");
  virtual ~User() = default;

		   bool get_access() const;
		   void set_access();
	
		   bool cmp_login(unsigned)    const;
		   bool cmp_password(unsigned) const;
	
		   string get_name() const;
		   void show_info()  const;
	
		   void new_login(unsigned);
		   void new_password(unsigned);

		   void edit_name();
		   void edit_email();
		   void edit_phone();

		   bool save(std::ofstream&);
private:   
};

