#include "Stat.h"

#include <iostream>
using std::cout;

#include <fstream>


void Stat::show_stat_base()
{
	cout << "\n Tests   :: "
			<< "attempts   " << "[" << total_attempts  << "] :: "
			<< "pause      " << "[" << total_paused    << "] :: "
			<< "complete   " << "[" << total_completed << "]";
	
	cout << "\n Average :: "
			<< "rating     " << "[" << avg_rating      << "] :: "
			<< "time       " << "[" << avg_time        << "]";

	cout << '\n';
}
void Stat::update_base_stat(Stat_user_test* stl)
{
	total_attempts++;
	
	if      (stl->test_status.status == Test_status::Status::paused)    total_paused++;
	else if (stl->test_status.status == Test_status::Status::completed)
	{
		total_completed++;
		
		avg_time =   (avg_time   + stl->get_time())   / 2;
		avg_rating = (avg_rating + stl->get_rating()) / 2;
	}
}

bool Stat::save_stat(std::ofstream& f_out)
{
	char c_out; unsigned u_out;
	
	f_out.write(reinterpret_cast<char*>(&(u_out = total_attempts)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = total_paused)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = total_completed)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = avg_time)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = avg_rating)), sizeof(unsigned));
	
	return true;
}
bool Stat::load_stat(std::ifstream& f_in)
{
	char c_in; unsigned u_in;
	
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); total_attempts = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); total_paused = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); total_completed = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); avg_time = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); avg_rating = u_in;
	
	return true;
}