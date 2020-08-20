#include "Question.h"
#include "Menu.h"

#include <iostream>
using std::cin;
using std::cout;

#include <fstream>


unsigned Question::counter_id = 0;
unsigned Question::get_counter_id() { return counter_id; }
void     Question::set_counter_id(unsigned counter_id) { Question::counter_id = counter_id; }

Question::Question() : id(counter_id++) {}
Question::Question(string& new_ask) : ask(move(new_ask)), id(counter_id++) { edit(); }

void     Question::def_user_choice() { user_choice = 0; }
void     Question::set_user_choice(unsigned choice)
{
	if (choice == 777)
	{
		unsigned new_choice = 0;
		while (new_choice < 1 || new_choice > ans.size())
		{
			cout << "\n Enter your choice # ";
			cin >> new_choice;
		}
		user_choice = new_choice;
	}
	else
	{
		if (choice < 1 || choice > ans.size()) user_choice = 0;
		user_choice = choice;
	}
}
unsigned Question::get_user_choice() const { return user_choice; }

void     Question::set_correct_ans()
{
	unsigned new_cor_ans = 0;
	while (new_cor_ans < 1 || new_cor_ans > ans.size())
	{
		cout << "\n Enter correct answer # ";
		cin >> new_cor_ans;
	}
	correct_ans = new_cor_ans;
}
unsigned Question::get_correct_ans() const { return correct_ans; }

void Question::edit()
{
	while (true)
	{
		system("cls");
		
		cout << "\n " << ask << "\n Answer : " << ans.size() << "\n";

		unsigned count_a = 0;
		for (auto& a : ans)
		{
			count_a++;
			cout << "\n "
				 << count_a << ") "
				 << a
			     << (count_a == correct_ans ? " [correct]" : "");
		}
		
		cout << "\n\n                 :::"
			 << "\n Add answer      [1]"
			 << "\n Del answer      [2]\n"
		
			 << "\n Change correct  [3]"
			 << "\n Replace ask     [4]\n"

			 << "\n Back            [8]"
			 << "\n Enter           [_]\b\b";
		Menu::enter_choice();

		if      (Menu::choice == '1') new_answer();
		else if (Menu::choice == '2') del_answer();
		else if (Menu::choice == '3') set_correct_ans();
		else if (Menu::choice == '4') replace_ask();

		else if (Menu::choice == '8')
		{
			if (ans.size() < 2)
			{
				cout << "\n More answers needed";
				new_answer();
			}
			if (correct_ans == 0) set_correct_ans();
			break;
		}
	}
	
}

void Question::replace_ask()
{
	bool replace_ask = true;
	while (replace_ask)
	{
		string new_ask;
		cout << "\n [new ask] : "; getline(cin, new_ask);
		cout <<   " [old ask] : " << ask << "\n";

		replace_ask = Menu::ask_yn("Replace?");
		if (replace_ask)
		{
			ask = new_ask;
			break;
		}
	}
}
void Question::new_answer()
{
	string new_ans;
	cout << "\n [new ans] : "; getline(cin, new_ans);
	ans.push_back(new_ans);
}
void Question::del_answer()
{
	unsigned number_a = 0;

	while (number_a < 1 || number_a > ans.size())
	{
		cout << "\n\n Answer #        ["
			<< (ans.size() < 10 ? "_" : "__")
			<< (ans.size() < 10 ? "]\b\b" : "]\b\b\b");
		cin >> number_a;
	}

	auto it_a = ans.begin();
	for (auto na = number_a; na != 1; --na) ++it_a;

	ans.erase(it_a);

	if (correct_ans == number_a)
	{
		cout << "\n Need correct answer!"
			 << "\n                 :::"
			 << "\n Choice in list  [1]"
			 << "\n Add new         [2]\n"

			 << "\n Enter           [_]\b\b";
		Menu::enter_choice();

		if (Menu::choice == '1')
		{
			unsigned count_a = 0;
			for (auto& a : ans) cout << "\n " << ++count_a << ") " << a;
			
			set_correct_ans();
		}
		if (Menu::choice == '2') new_answer();
	}
}

bool Question::save(std::ofstream& f_out)
{
	char c_out; unsigned u_out;

	f_out.write(reinterpret_cast<char*>(&(u_out = correct_ans)), sizeof(unsigned));
	f_out.write(reinterpret_cast<char*>(&(u_out = id)), sizeof(unsigned));

	f_out.write(reinterpret_cast<char*>(&(u_out = ask.length())), sizeof(unsigned));
	for (auto& it_ask : ask) f_out.write(&(c_out = it_ask), sizeof(char));

	f_out.write(reinterpret_cast<char*>(&(u_out = ans.size())), sizeof(unsigned));
	for (auto& it_ans : ans)
	{
		f_out.write(reinterpret_cast<char*>(&(u_out = it_ans.length())), sizeof(unsigned));
		for (auto& it_s : it_ans) f_out.write(&(c_out = it_s), sizeof(char));
	}
	
	return true;
}
bool Question::load(std::ifstream& f_in)
{
	char c_in; unsigned u_in, size, size_str;
	string str_tmp;

	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); correct_ans = u_in;
	f_in.read(reinterpret_cast<char*>(&u_in), sizeof(unsigned)); id = u_in;

	f_in.read(reinterpret_cast<char*>(&size_str), sizeof(unsigned));
	str_tmp.resize(size_str);
	for (unsigned j = 0; j < static_cast<int>(str_tmp.size()); ++j)
		if (f_in.read(&c_in, sizeof(char)))
			str_tmp[j] = c_in;
	ask = str_tmp;

	f_in.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	for (unsigned i = 0; i < size; ++i)
	{
		f_in.read(reinterpret_cast<char*>(&size_str), sizeof(unsigned));
		str_tmp.clear(); str_tmp.resize(size_str);
		for (unsigned j = 0; j < static_cast<int>(str_tmp.size()); ++j)
			if (f_in.read(&c_in, sizeof(char)))
				str_tmp[j] = c_in;
		ans.push_back(str_tmp);
	}
	
	return true;
}
