#include "Stat_user_test.h"

#include <iostream>
using std::cout;

#include <fstream>

Stat_user_test::Stat_user_test ( unsigned id,
								 string section_name, string test_name, 
                                 Test_status test_status,
                                 unsigned total_answers, unsigned time, unsigned correct_answers, unsigned rating )

		                       : id(id),
								 section_name(section_name), test_name(test_name),
								 test_status(test_status),
	                             total_answers(total_answers), correct_answers(correct_answers), time(time), rating(rating)
{/*-*/}

void Stat_user_test::update_user_stat(unsigned total_answers, unsigned time, unsigned correct_answers, unsigned rating)
{
	this->total_answers   = total_answers;
	this->time            = time;
	this->correct_answers = correct_answers;
	this->rating          = rating;
}

void Stat_user_test::show_stat_test() const
{
	cout << "\n " << section_name << " :: " << test_name << " :: " << test_status.print() << " :: "
			<< "time [" << time << "] : "
			<< "rating [" << correct_answers << "/" << total_answers << " | " << rating << "] ";
}

string   Stat_user_test::get_test_name()       const { return test_name; }
string   Stat_user_test::get_section_name()    const { return section_name; }

unsigned Stat_user_test::get_rating()          const { return rating; }
unsigned Stat_user_test::get_time()            const { return time; }
unsigned Stat_user_test::get_total_answers()   const { return total_answers; }
unsigned Stat_user_test::get_correct_answers() const { return correct_answers; }

bool Stat_user_test::save_user_test_list(std::ofstream& f_out)
{
	char c_out; unsigned u_out;
	
	f_out.write(reinterpret_cast<char*>(&(u_out = test_name.length())), sizeof(unsigned));
	for (auto& it_s : test_name) f_out.write(&(c_out = it_s), sizeof(char));

	f_out.write(reinterpret_cast<char*>(&(u_out = section_name.length())), sizeof(unsigned));
	for (auto& it_s : section_name) f_out.write(&(c_out = it_s), sizeof(char));

	f_out.write(reinterpret_cast<char*>(&(u_out = rating)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = time)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = total_answers)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = correct_answers)), sizeof(unsigned));

	f_out.write(reinterpret_cast<char*>(&(u_out = id)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = test_status.status)), sizeof(unsigned));

	f_out.write(reinterpret_cast<char*>(&(u_out = answer_list.size())), sizeof(unsigned));
	for (auto& it_al : answer_list)
	{
		f_out.write(reinterpret_cast<char*>(&(u_out = it_al.first)), sizeof(unsigned));
		f_out.write(reinterpret_cast<char*>(&(u_out = it_al.second)), sizeof(unsigned));
	}
	
	return true;
}
bool Stat_user_test::load_user_test_list(std::ifstream& f_in)
{
	char c_in; unsigned u_in, size;
	string str;

	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	str.resize(size);
	for (unsigned j = 0; j < static_cast<int>(str.size()); ++j)
		if (f_in.read(&c_in, sizeof(char)))
			str[j] = c_in;
	test_name = str;
	
	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	str.clear(); str.resize(size);
	for (unsigned j = 0; j < static_cast<int>(str.size()); ++j)
		if (f_in.read(&c_in, sizeof(char)))
			str[j] = c_in;
	section_name = str;

	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); rating = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); time = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); total_answers = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); correct_answers = u_in;
	
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); id = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); test_status.status = Test_status::Status(u_in);

	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned f, s;
		f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); f = u_in;
		f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); s = u_in;
		
		answer_list.emplace(f, s);
	}
	
	return true;
}



