#include "User.h"

#include <iostream>
using std::cin;
using std::cout;

#include "Menu.h"

#include <fstream>

User::User(bool is_admin, unsigned& login, unsigned& password, string name, string phone, string email)
: login(login), password(password),
  name(move(name)), email(move(email)), phone(move(phone)),
  is_admin(is_admin)
{/*-*/}

bool User::get_access() const { return is_admin; }
void User::set_access()
{
	if (is_admin)
	{
		cout << "\n " << name << " is admin!\n";
		if (Menu::ask_yn("Remove admin access?")) is_admin = false;
	}
	else
	{
		is_admin = true;
		cout << "\n " << name << " is admin!\n";
	}
}

bool User::cmp_login(unsigned login) const { return this->login == login; }
bool User::cmp_password(unsigned password) const { return this->password == password; }

string User::get_name() const { return name; }

void User::show_info() const
{
	cout << "\n Name "  << name  << " :: "
			<< "Email " << email << " : "
			<< "Phone " << phone
			<< (get_access() ? " : [admin]" : "");
	
	cout << '\n';
}

void User::new_login(unsigned new_login)       { login    = new_login; }
void User::new_password(unsigned new_password) { password = new_password; }

void User::edit_name()  { cout << "\n Enter new name: ";  getline(cin, name);  }
void User::edit_email() { cout << "\n Enter new email: "; getline(cin, email); }
void User::edit_phone() { cout << "\n Enter new phone: "; getline(cin, phone); }

bool User::save(std::ofstream& f_out)
{
	char c_out; unsigned u_out;

	f_out.write(reinterpret_cast<char*>(&(u_out = login)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = password)), sizeof(unsigned));

	f_out.write(reinterpret_cast<char*>(&(u_out = name.length())), sizeof(unsigned));
	for (auto& it_s : name) f_out.write(&(c_out = it_s), sizeof(char));

	f_out.write(reinterpret_cast<char*>(&(u_out = email.length())), sizeof(unsigned));
	for (auto& it_s : email) f_out.write(&(c_out = it_s), sizeof(char));

	f_out.write(reinterpret_cast<char*>(&(u_out = phone.length())), sizeof(unsigned));
	for (auto& it_s : phone) f_out.write(&(c_out = it_s), sizeof(char));

	f_out.write(reinterpret_cast<char*>(&(u_out = is_admin)), sizeof(unsigned));

	save_stat(f_out); 

	f_out.write(reinterpret_cast<char*>(&(u_out = user_test_list.size())), sizeof(unsigned));
	for (auto& it_utl : user_test_list) it_utl->save_user_test_list(f_out);
	
	return true;
}