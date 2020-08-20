#include "Test.h"
#include "Menu.h"

#include <iostream>
using std::cin;
using std::cout;

#include <algorithm>
#include <ctime>

#include <fstream>


unsigned Test::counter_id = 0;

Test::Test() : id(counter_id++) {}
unsigned Test::get_counter_id() { return counter_id; }
void     Test::set_counter_id(unsigned counter_id) { Test::counter_id = counter_id; }

void Test::scan()
{
	if (questions.empty())
	{
		cout << "\n There are no questions in the test";
		if (Menu::ask_yn("Add new questions?")) add_questions();
		else return;
	}
	
	unsigned count_q = 1;
	auto q = questions.begin();
	while (true)
	{
		system("cls");
		cout << "\n [#" << count_q << "/" << questions.size() << "] " << (*q)->ask << "\n";

		unsigned count_a = 0;
		for (auto& a : (*q)->ans)
		{
			count_a++;
			cout << "\n " << count_a << ") "
				 << a
				 << (count_a == (*q)->get_correct_ans() ? " [correct]" : "");
		}
			
		cout << "\n                 :::"
		     << "\n Prev            [1]"
			 << "\n Next            [2]\n"

			 << "\n Edit            [3]\n"

			 << "\n Back            [8]"
			 << "\n Enter           [_]\b\b";
		Menu::enter_choice();
		
		if      (Menu::choice == '1')
		{
			if (q == questions.begin())
			{
				q = questions.end();
				--q;
				count_q = questions.size();
			}
			else
			{
				--q;
				--count_q;
			}
		}
		else if (Menu::choice == '2')
		{
			++q;
			if (q == questions.end())
			{
				q = questions.begin();
				count_q = 1;
			} 
			else ++count_q;
		}
		else if (Menu::choice == '3') (*q)->edit();
		else break;
	}
}

Stat_user_test* Test::testing(User* user, string section_name, string test_name)
{
	if (questions.empty())
	{
		cout << "\n There are no questions in the test";
		user->user_test_list.push_back(new Stat_user_test(id, section_name, test_name, Test_status(Test_status::Status::unknown)));
		return user->user_test_list.back();
	}

	
	Stat_user_test* it_utl = nullptr;
	for (auto& utl : user->user_test_list)
	{
		if (utl->id == id && utl->test_status.status == Test_status::Status::paused)
		{
			it_utl = utl;
			break;
		}
	}
	if (not it_utl)
	{
		user->user_test_list.push_back(new Stat_user_test(id, section_name, test_name, Test_status(Test_status::Status::unknown)));
		it_utl = user->user_test_list.back();
	}

	std::random_shuffle(questions.begin(), questions.end());
	for (auto& q_tmp : questions)
	{
		for (auto& a_tmp : it_utl->answer_list)
		{
			if (q_tmp->id == a_tmp.first) q_tmp->set_user_choice(a_tmp.second);
		}
	}
	
	unsigned count_q = 1;
	auto it_q = questions.begin();
	time_t total_time = time(0);
	while (true)
	{
		system("cls");
		cout << "\n [#" << count_q << "/" << questions.size() << "] " << (*it_q)->ask << "\n";

		unsigned count_a = 0;
		for (auto& a : (*it_q)->ans)
		{
			count_a++;
			cout << "\n " << count_a << ") "
				 << a
				 << (count_a == (*it_q)->get_user_choice() ? " [choice]" : "");
		}

		cout << "\n                 :::"
			 << "\n Prev            [1]"
			 << "\n Next            [2]\n"
		
			 << "\n Choice          [3]\n"

			 << "\n Back            [8]"
			 << "\n Enter           [_]\b\b";
		Menu::enter_choice();

		if (Menu::choice == '1')
		{
			if (it_q == questions.begin())
			{
				it_q = questions.end();
				--it_q;
				count_q = questions.size();
			}
			else
			{
				--it_q;
				--count_q;
			}
		}
		else if (Menu::choice == '2')
		{
			++it_q;
			if (it_q == questions.end())
			{
				it_q = questions.begin();
				count_q = 1;
			}
			else ++count_q;
		}
		else if (Menu::choice == '3') (*it_q)->set_user_choice();
		else if (Menu::choice == '8')
		{
			unsigned count_q_tmp = 1;
			bool is_break = false;
			for (auto& q : questions)
			{
				if (q->get_user_choice() == 0)
				{
					cout << "\n Have unfinished questions #" << count_q_tmp;
					if (Menu::ask_yn("Pause the test?"))
					{
						for (auto& q_tmp : questions)
						{
							user->user_test_list.back()->answer_list.emplace(q_tmp->id, q_tmp->get_user_choice());
							q_tmp->def_user_choice();
						}
						
						it_utl->test_status.status = Test_status::Status::paused;
						it_utl->update_user_stat(questions.size(), time(0) - total_time);
						update_base_stat(it_utl);
						
						is_break = true;
						break;
					}
				}
				count_q_tmp++;
			}

			if (is_break) return it_utl;
			else
			{
				if (Menu::ask_yn("End test?"))
				{
					double cor_ans_tmp = 0;
					for (auto& q : questions)
					{
						if (q->get_user_choice() == q->get_correct_ans()) cor_ans_tmp++;
						q->def_user_choice();
					}

					unsigned t = time(0) - total_time, r = 12 * (cor_ans_tmp / questions.size());
					
					it_utl->test_status.status = Test_status::Status::completed;
					it_utl->update_user_stat(questions.size(), t, cor_ans_tmp, r);
					update_base_stat(it_utl);

					system("cls");
					it_utl->show_stat_test();

					cout << "\n\n ";
					system("pause");
					
					return it_utl;
				}
			}
		}
	}
}

void Test::add_questions()
{
	string new_ask;
	cout << "\n [new ask] : ";
	
	if (cin.peek() == '\n') cin.ignore();
	getline(cin, new_ask);
	
	questions.push_back(new Question(new_ask));
}

bool Test::save(std::ofstream& f_out)
{
	char c_out; unsigned u_out;

	f_out.write(reinterpret_cast<char*>(&(u_out = id)), sizeof(unsigned));
	
	f_out.write(reinterpret_cast<char*>(&(u_out = questions.size())), sizeof(unsigned));
	for (auto& it_q : questions) it_q->save(f_out);

	save_stat(f_out);
	
	return true;
}
bool Test::load(std::ifstream& f_in)
{
	char c_in; unsigned u_in, size;

	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); id = u_in;

	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	for (unsigned i = 0; i < size; ++i)
	{
		Question* tmp_que = new Question;
		questions.push_back(tmp_que);

		tmp_que->load(f_in);
	}

	load_stat(f_in);
	
	return true;
}