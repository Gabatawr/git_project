#include "Tesys.h"

#include <fstream>


bool Tesys::check_admin()
{
	if (not users.empty()) 
		for (auto& i : users) 
			if (i.second->get_access() == true) return true;
	
	return false;
}

User* Tesys::try_login(unsigned login, unsigned password)
{
	User* user = users[login];
	if (user && user->cmp_password(password)) return user;
	return nullptr;
}

void Tesys::add_section()
{
	string new_section;
	cout << "\n New section name: ";
	
	if (cin.peek() == '\n') cin.ignore();
	getline(cin, new_section);
	
	sections.emplace(new_section, new Section);
}

bool Tesys::save(std::ofstream& f_out)
{
	char c_out; unsigned u_out;
	
	f_out.write(reinterpret_cast<char*>(&(u_out = users.size())), sizeof(unsigned));
	for (auto& it_u : users) it_u.second->save(f_out);
	
	f_out.write(reinterpret_cast<char*>(&(u_out = sections.size())), sizeof(unsigned)); 
	for (auto it_s = sections.begin(); it_s != sections.end(); ++it_s)
	{
		f_out.write(reinterpret_cast<char*>(&(u_out = it_s->first.length())), sizeof(unsigned));
		for (auto& it_c : it_s->first) f_out.write(&(c_out = it_c), sizeof(char));

		it_s->second->save(f_out);
	}

	return true;
}
Tesys::Tesys(string& file_name)
{
	std::ifstream f_in(file_name, std::ios::binary);
	if (not f_in.is_open()) { cout << " File not open.."; return; }

	char c_in; unsigned u_in, size;
	
	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned login, password, size_str, size_tmp;
		string name, email, phone;
		bool is_admin;
		
		f_in.read(reinterpret_cast<char*>(&login), sizeof(unsigned));
		f_in.read(reinterpret_cast<char*>(&password), sizeof(unsigned));
		
		f_in.read(reinterpret_cast<char*>(&size_str), sizeof(unsigned));
		name.resize(size_str);
		for (unsigned j = 0; j < static_cast<int>(name.size()); ++j)
			if (f_in.read(&c_in, sizeof(char)))
				name[j] = c_in;

		f_in.read(reinterpret_cast<char*>(&size_str), sizeof(unsigned));
		email.resize(size_str);
		for (unsigned j = 0; j < static_cast<int>(email.size()); ++j)
			if (f_in.read(&c_in, sizeof(char)))
				email[j] = c_in;

		f_in.read(reinterpret_cast<char*>(&size_str), sizeof(unsigned));
		phone.resize(size_str);
		for (unsigned j = 0; j < static_cast<int>(phone.size()); ++j)
			if (f_in.read(&c_in, sizeof(char)))
				phone[j] = c_in;

		f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); is_admin = u_in;
		
		User* user_tmp = new User(is_admin, login, password, name, phone, email);
		users.emplace(login, user_tmp);

		user_tmp->load_stat(f_in);

		f_in.read(reinterpret_cast<char*>(&size_tmp), sizeof(unsigned));
		for (unsigned j = 0; j < size_tmp; ++j)
		{
			user_tmp->user_test_list.push_back(new Stat_user_test);
			user_tmp->user_test_list.back()->load_user_test_list(f_in);
		}
	}

	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned size_str;
		string name;

		f_in.read(reinterpret_cast<char*>(&size_str), sizeof(unsigned));
		name.clear(); name.resize(size_str);
		for (unsigned j = 0; j < static_cast<int>(name.size()); ++j)
			if (f_in.read(&c_in, sizeof(char)))
				name[j] = c_in;

		Section* tmp_sec = new Section;
		sections.emplace(name, tmp_sec);

		tmp_sec->load(f_in);
	}
}