#include "Section.h"

#include <iostream>
using std::cout;
using std::cin;

#include <fstream>

void Section::add_test()
{
	string new_test;
	cout << "\n New test name: ";

	if (cin.peek() == '\n') cin.ignore();
	getline(cin, new_test);
	
	tests.emplace(new_test, new Test);
}

bool Section::save(std::ofstream& f_out)
{
	char c_out; unsigned u_out;

	f_out.write(reinterpret_cast<char*>(&(u_out = Test::get_counter_id())), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = Question::get_counter_id())), sizeof(unsigned));
	
	f_out.write(reinterpret_cast<char*>(&(u_out = tests.size())), sizeof(unsigned));
	for (auto it_t = tests.begin(); it_t != tests.end(); ++it_t)
	{
		f_out.write(reinterpret_cast<char*>(&(u_out = it_t->first.length())), sizeof(unsigned));
		for (auto& it_s : it_t->first) f_out.write(&(c_out = it_s), sizeof(char));

		it_t->second->save(f_out);
	}
	
	save_stat(f_out);

	return true;
}
bool Section::load(std::ifstream& f_in)
{
	char c_in; unsigned u_in, size;

	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); Test::set_counter_id(u_in);
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); Question::set_counter_id(u_in);

	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned size_str;
		string name;

		f_in.read(reinterpret_cast<char*>(&size_str), sizeof(unsigned));
		name.resize(size_str);
		for (unsigned j = 0; j < static_cast<int>(name.size()); ++j)
			if (f_in.read(&c_in, sizeof(char)))
				name[j] = c_in;

		Test* tmp_test = new Test;
		tests.emplace(name, tmp_test);

		tmp_test->load(f_in);
	}
	
	return true;
}
