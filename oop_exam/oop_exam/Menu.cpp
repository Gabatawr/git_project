#include "Menu.h"

using std::exception;

#include <iostream>
using std::cin;
using std::cout;

#include <iomanip>

#include "conio.h"
#include <fstream>

int int_count (string str)
{
	int count = 0;
	for (auto i = 0; str[i] != '\0'; i++)
	{
		bool flag = false;

		int digits = i;
		while (str[i] >= 48 && str[i] <= 57) {
			flag = true;
			i++;
		}
		digits = i - digits;

		if (digits > 0) count++;
		if (flag) i--;
	}
	return count;
}
int int_pos   (string str, unsigned number_in_row = 1)
{
	if (int_count(str) == 0) return -1;

	double number = 0;
	for (unsigned i = 0, count = 0; i < str.length(); i++)
	{
		bool flag = false;

		unsigned digits = i;
		while (str[i] >= 48 && str[i] <= 57) {
			flag = true;
			i++;
		}
		digits = i - digits;

		if (digits > 0) count++;

		if (count == number_in_row)
		{
			i -= digits;
			for (unsigned j = 0; j < digits; j++, i++)
			{
				number += static_cast<double>(str[i] - 48) / 10;
				number *= 10;
			}
			return static_cast<int>(number);
		}
		if (flag) i--;
	}
	return -1;
}

char Menu::choice = '0';

void Menu::enter_choice(bool is_yn)
{
	char ch, tmp;
	unsigned count = 0;

	while ((ch = _getch()) != '\r')
	{
		if      (is_yn && (ch == 'y' || ch == 'n') && count == 0)
		{
			cout << ch;
			tmp = ch;
			count++;
		}
		else if (not is_yn && ch > 47 && ch < 58 && count == 0)
		{
			cout << ch;
			tmp = ch;
			count++;
		}
		else if (count == 1 && ch == '\b')
		{
			count--;
			cout << ch << '_' << ch;
		}
	}
	choice = tmp;
	cout << '\n';
}
bool Menu::ask_yn(const char* question)
{
	while (true) 
	{
		cout << "\n " << question << " [y/n] _\b";
		enter_choice(true);
		
		if (choice == 'y' || choice == 'Y') return true;
		if (choice == 'n' || choice == 'N') return false;
		cout << "\n Invalid command..";
	}
}

void Menu::enter_login()
{
	while (true)
	{
		cout << "\n Enter login: ";
		login.clear();

		getline(cin, login);
		if (login.length() < 3)
		{
			cout << "\n oops, login is very short\n";
			continue;
		}

		e_login = encrypt(login);
		break;
	}
}
void Menu::enter_password()
{
	while (true)
	{
		cout << " Enter password: ";
		password.clear();

		char ch;
		while ((ch = _getch()) != '\r')
		{
			if (ch == '\b')
			{
				cout << ch << " " << ch;
				password.pop_back();
			}
			else
			{
				password.push_back(ch);
				cout << "*";
			}
		}

		if (password.length() < 3)
		{
			cout << "\n oops, password is very short\n";
			continue;
		}

		e_password = encrypt(password);
		break;
	}
}
void Menu::enter_optional()
{
	while (true)
	{
		cout << "\n Enter full name: ";
		getline(cin, name);

		if (name.size() < 2) cout << " Incorrect name..\n";
		else break;
	}

	while (true)
	{
		cout << " Enter @mail: ";
		getline(cin, email);

		if ( email.find('@') == string::npos ||
			 email.find('.') == string::npos ||
			 email.find('@') == 0 ||
			 email.find('.') == email.size() - 1 )

			cout << " Incorrect email..\n\n";
		
		else break;
	}
	
	cout << " Enter phone: ";
	getline(cin, phone);
}

void Menu::sign_up(bool access)
{
	cout << "\n Create new user:\n";
	while (true)
	{
		enter_login();
		enter_password();
		if (tesys.users.find(e_login) != tesys.users.end())
			cout << "\n oops, login must be unique";
		else break;
	}
	
	if (ask_yn("\n Nice, would you like to enter your details now?"))
	{
		enter_optional();
		tesys.users.emplace( e_login,  new User(access,e_login, e_password, name, phone, email));
	}
	else tesys.users.emplace(e_login, new User(access, e_login, e_password));
}
void Menu::sign_in()
{
	while (true) 
	{
		enter_login();	
		enter_password();
		
		if ((user = tesys.try_login(e_login, e_password)) == nullptr) cout << "\n\n Invalid login or password..";
		else break;

		if (not ask_yn("Try again?")) return;
	} 
}

void Menu::menu_login()
{
	while (user == nullptr)
	{
		system("cls");
		
		cout << "\n                 :::"
		     << "\n Sign in         [1]"
			 << "\n Sign up         [2]\n"
		
			 << "\n Exit            [0]\n"
		
			 << "\n Enter           [_]\b\b";
		enter_choice();
		
		if      (choice == '1') sign_in();
		else if (choice == '2') sign_up();
		else if (choice == '0') throw(exception("exit"));
		
		else cout << "\n Invalid command..";
	}
}
void Menu::menu_stat()
{
	while (user != nullptr)
	{
		system("cls");
		if (not user->get_access()) user->show_stat_base();
		
		    cout << "\n                 :::"
		         << "\n By sections     [1]"
			     << "\n By tests        [2]\n";
		if (user->get_access())
		{
			cout   << " By users        [3]\n";
		}
		    cout << "\n Back            [8]"
				 << "\n Logout          [9]"
			     << "\n Exit            [0]\n"
		
			     << "\n Enter           [_]\b\b";
		    enter_choice();
		
		if (user->get_access())
		{
			if (choice == '1' || choice == '2')
			{
				unsigned number_s, count_s = 0;
				
				cout << "\n Sections list ";
				for (auto& s : tesys.sections) 
					cout << "\n " << std::left << std::setw(16) << s.first << std::right << "[" << ++count_s << "]";

				if (count_s > 0)
				{
					while (true)
					{
						cout << "\n\n Section #       ["
							<< (count_s < 10 ? "_" : "__")
							<< (count_s < 10 ? "]\b\b" : "]\b\b\b");
						cin >> number_s;

						if (number_s == 0 || number_s > count_s) cout << "\n Invalid command..";
						else break;
					}

					auto it_s = tesys.sections.begin();
					for (auto ns = number_s; ns != 1; --ns) ++it_s;

					if      (choice == '1') 
					{
						it_s->second->show_stat_base();
						
						cout << "\n ";
						system("pause");
					}
					else if (choice == '2')
					{
						unsigned number_t, count_t = 0;

						cout << "\n Tests list      :::";
						for (auto& t : it_s->second->tests)
							cout << "\n " << std::left << std::setw(16) << t.first << std::right << "[" << ++count_t << "]";

						if (count_t > 0)
						{
							while (true)
							{
								cout << "\n\n Test #          ["
									<< (count_t < 10 ? "_" : "__")
									<< (count_s < 10 ? "]\b\b" : "]\b\b\b");
								cin >> number_t;

								if (number_t == 0 || number_t > count_t) cout << "\n Invalid command..";
								else break;
							}

							auto it_t = it_s->second->tests.begin();
							for (auto nt = number_t; nt != 1; --nt) ++it_t;

							it_t->second->show_stat_base();
							
							cout << "\n ";
							system("pause");
						}
						else 
						{
							cout << "\n Not found \n\n ";
							system("pause");
						}
					}
				}
				else 
				{
					cout << "\n Not found \n\n ";
					system("pause");
				}
			}
			else if (choice == '3')
			{
				unsigned number_u, count_u = 0;

				cout << "\n Users list      :::";
				for (auto& u : tesys.users)
					cout << "\n " << std::left << std::setw(16) << u.second->get_name()
						 << std::right << "[" << ++count_u << "]"
						 << (u.second->get_access() ? "[a]" : "");

				if (count_u > 0)
				{
					while (true)
					{
						cout << "\n\n User #          ["
							<< (count_u < 10 ? "_" : "__")
							<< (count_u < 10 ? "]\b\b" : "]\b\b\b");
						cin >> number_u;

						if (number_u == 0 || number_u > count_u) cout << "\n Invalid command..";
						else break;
					}

					auto it_u = tesys.users.begin();
					for (auto nu = number_u; nu != 1; --nu) ++it_u;

					it_u->second->show_info();
					it_u->second->show_stat_base();

					cout << "\n ";
					system("pause");
				}
				else 
				{
					cout << "\n Not found \n\n ";
					system("pause");
				}
			}
		}
		else
		{
			if      (choice == '1')
			{
				unsigned number_s, count_s = 0;
				
				cout << "\n Sections list   :::";
				for (auto& s : tesys.sections)
					cout << "\n " << std::left << std::setw(16) << s.first << std::right << "[" << ++count_s << "]";

				if (count_s > 0)
				{
					while (true)
					{
						cout << "\n\n Section #       ["
							<< (count_s < 10 ? "_" : "__")
							<< (count_s < 10 ? "]\b\b" : "]\b\b\b");
						cin >> number_s;

						if (number_s == 0 || number_s > count_s) cout << "\n Invalid command..";
						else break;
					}

					auto it_s = tesys.sections.begin();
					for (auto ns = number_s; ns != 1; --ns) ++it_s;

					user->show_stat_sections(it_s->first);
				}
				else 
				{
					cout << "\n Not found \n\n ";
					system("pause");
				}
			}
			else if (choice == '2') user->show_stat_tests();
		}
		
		if      (choice == '8') menu_one();
		else if (choice == '9') user = nullptr;
		else if (choice == '0') throw(exception("exit"));
	}
}
void Menu::menu_one()
{
	while (user != nullptr)
	{
		    system("cls");
			cout << "\n Welcom in Tesys, " << user->get_name() << "!\n";

			cout << "\n                 :::";
		    cout << "\n Statistics      [1]\n";
		if (user->get_access())
		{
			cout << "\n User management [2]"
				 << "\n Test management [3]\n";
		}
		else 
		{
			cout << "\n Testing         [2]";
			cout << "\n Profile         [3]\n";
		}
			cout << "\n Logout          [9]"
				 << "\n Exit            [0]\n"
		
				 << "\n Enter           [_]\b\b";
			enter_choice();
		
		if (choice == '1')
		{
			menu_stat();
			continue;
		}
		if (user->get_access())
		{
			if      (choice == '2')
			{
				unsigned number_u, count_u = 0;

				cout << "\n Users list      :::";
				for (auto& u : tesys.users)
					cout << "\n " << std::left << std::setw(16) << u.second->get_name()
						 << std::right << "[" << ++count_u << "]"
						 << (u.second->get_access() ? "[a]" : "");

				if (count_u > 0)
				{
					
					while (true)
					{
						cout << "\n Enter           [" << (count_u < 10 ? "_" : "__") << "]\b\b";
						cin >> number_u;

						if (number_u == 0 || number_u > count_u) cout << "\n Invalid command..";
						else break;
					}

					auto it_u = tesys.users.begin();
					for (auto nu = number_u; nu != 1; --nu) ++it_u;
					
					while (true)
					{
						system("cls");
						it_u->second->show_info();

						cout << "\n                 :::";
						cout << "\n New login       [1]"
							 << "\n New Password    [2]\n"
						
							 << "\n Edit name       [3]"
							 << "\n Edit email      [4]"
							 << "\n Edit phone      [5]\n"

							 << "\n Admin access    [6]\n"

							 << "\n Back            [8]"
							 << "\n Enter           [_]\b\b";
						enter_choice();

						if (choice == '1' || choice == '2')
						{
							User* edit_user = it_u->second;

							if (choice == '1')
							{
								tesys.users.erase(it_u);

								enter_login();

								edit_user->new_login(e_login);
								tesys.users.emplace(e_login, edit_user);

								it_u = tesys.users.find(e_login);
							}
							else if (choice == '2')
							{
								cout << "\n";
								enter_password();

								e_password = encrypt(password);

								edit_user->new_password(e_password);
							}
						}
						else if (choice == '3') it_u->second->edit_name();
						else if (choice == '4') it_u->second->edit_email();
						else if (choice == '5') it_u->second->edit_phone();
						else if (choice == '6') it_u->second->set_access();

						else if (choice == '8') break;
					}
				}
				else 
				{
					cout << "\n Not found \n\n ";
					system("pause");
				}
			}
			else if (choice == '3')
			{
				while (true)
				{
					system("cls");
					
					unsigned number_s, count_s = 0;

					cout << "\n Sections list   :::";
					for (auto& s : tesys.sections)
						cout << "\n " << std::left << std::setw(16) << s.first << std::right << "[" << ++count_s << "]";

					if (count_s > 0)
					{
						cout << "\n\n                 :::"
						     << "\n Add section     [1]"
							 << "\n Choice section  [2]\n"

							 << "\n Back            [8]\n"

							 << "\n Enter           [_]\b\b";
						enter_choice();

						if      (choice == '1') tesys.add_section();
						else if (choice == '2')
						{
							while (true)
							{
								cout << "\n\n Section #       ["
									 << (count_s < 10 ? "_" : "__")
									 << (count_s < 10 ? "]\b\b" : "]\b\b\b");
								cin >> number_s;

								if (number_s == 0 || number_s > count_s) cout << "\n Invalid command..";
								else break;
							}

							auto it_s = tesys.sections.begin();
							for (auto ns = number_s; ns != 1; --ns) ++it_s;

							while (true)
							{
								system("cls");
								unsigned number_t, count_t = 0;
								
								cout << "\n " << it_s->first << " :: "
									 << "tests : " << it_s->second->tests.size() << "\n";
								
								cout << "\n Tests list      :::";
								for (auto& t : it_s->second->tests)
									cout << "\n " << std::left << std::setw(16) << t.first << std::right << "[" << ++count_t << "]";

								if (count_t > 0)
								{
									cout << "\n\n                 :::"
										 << "\n Add test        [1]"
										 << "\n Choice test     [2]\n"

										 << "\n Del section     [3]"
										 << "\n Back            [8]\n"

										 << "\n Enter           [_]\b\b";
									enter_choice();

									if      (choice == '1') it_s->second->add_test();
									else if (choice == '2')
									{
										while (true)
										{
											cout << "\n\n Test #          ["
												 << (count_t < 10 ? "_" : "__")
												 << (count_s < 10 ? "]\b\b" : "]\b\b\b");
											cin >> number_t;

											if (number_t == 0 || number_t > count_t) cout << "\n Invalid command..";
											else break;
										}

										auto it_t = it_s->second->tests.begin();
										for (auto nt = number_t; nt != 1; --nt) ++it_t;

										while (true)
										{
											system("cls");
											
											cout << "\n " << it_t->first << " :: "
												<< "questions : " << it_t->second->questions.size();

											cout << "\n\n                 :::"
											     << "\n Add questions   [1]"
												 << "\n Scan mode       [2]\n"
											
												 << "\n Del test        [3]\n"
											
												 << "\n Back            [8]"
												 << "\n Enter           [_]\b\b";
											enter_choice();

											if      (choice == '1') it_t->second->add_questions();
											else if (choice == '2') it_t->second->scan();
											else if (choice == '3' && ask_yn("Delete this test?"))
											{
												it_s->second->tests.erase(it_t);
												break;
											}
													
											else if (choice == '8') break;
										}
									}
									else if (choice == '3' && ask_yn("Delete this section?"))
									{
										tesys.sections.erase(it_s);
										break;
									}
									
									else if (choice == '8') break;
								}
								else
								{
									cout << "\n Not found \n\n ";
									system("pause");

									system("cls");
									
									cout << "\n\n                 :::"
									     << "\n Add new test    [1]"
										 << "\n Back            [8]\n"

										 << "\n Enter           [_]\b\b";
									enter_choice();

									if      (choice == '1') it_s->second->add_test();

									else if (choice == '8') break;
								}
							}
						}
						else if (choice == '8') break;
					}
					else
					{
						cout << "\n Not found \n\n ";
						system("pause");

						system("cls");
						cout << "\n\n                 :::"
						     << "\n Add new section [1]"
							 << "\n Back            [8]\n"

							 << "\n Enter           [_]\b\b";
						enter_choice();

						if      (choice == '1') tesys.add_section();

						else if (choice == '8') break;
					}
				}
			}
		}
		else
		{
			if      (choice == '2')
			{
				while (true)
				{
					system("cls");

					unsigned number_s, count_s = 0;

					cout << "\n Sections list   :::";
					for (auto& s : tesys.sections)
						cout << "\n " << std::left << std::setw(16) << s.first << std::right << "[" << ++count_s << "]";

					if (count_s > 0)
					{
						cout << "\n                 :::"
							 << "\n Choice section  [1]\n"
						
							 << "\n Back            [8]"
							 << "\n Enter           [_]\b\b";
						enter_choice();

						if      (choice == '1')
						{
							while (true)
							{
								cout << "\n\n Section #       ["
									<< (count_s < 10 ? "_" : "__")
									<< (count_s < 10 ? "]\b\b" : "]\b\b\b");
								cin >> number_s;

								if (number_s == 0 || number_s > count_s) cout << "\n Invalid command..";
								else break;
							}

							auto it_s = tesys.sections.begin();
							for (auto ns = number_s; ns != 1; --ns) ++it_s;

							while (true)
							{
								system("cls");
								unsigned number_t, count_t = 0;

								cout << "\n " << it_s->first << " :: "
									<< "tests : " << it_s->second->tests.size() << "\n";

								cout << "\n Tests list      :::";
								for (auto& t : it_s->second->tests)
									cout << "\n " << std::left << std::setw(16) << t.first << std::right << "[" << ++count_t << "]";

								if (count_t > 0)
								{
									cout << "\n                 :::"
										 << "\n Choice test     [1]\n"
									
										 << "\n Back            [8]"
										 << "\n Enter           [_]\b\b";
									enter_choice();
									
									if      (choice == '1')
									{
										while (true)
										{
											cout << "\n\n Test #          ["
												 << (count_t < 10 ? "_" : "__")
												 << (count_s < 10 ? "]\b\b" : "]\b\b\b");
											cin >> number_t;

											if (number_t == 0 || number_t > count_t) cout << "\n Invalid command..";
											else break;
										}

										auto it_t = it_s->second->tests.begin();
										for (auto nt = number_t; nt != 1; --nt) ++it_t;

										Stat_user_test* it_utl = it_t->second->testing(user, it_s->first, it_t->first);
										it_s->second->update_base_stat(it_utl);
										user->update_base_stat(it_utl);
									}

									else if (choice == '8') break;
								}
								else
								{
									cout << "\n Not found \n\n ";
									system("pause");
								}
							}
						}
						else if (choice == '8') break;
					}
					else
					{
						cout << "\n Not found \n\n ";
						system("pause");
					}
				}
			}
			else if (choice == '3')
			{
				while (true)
				{
					system("cls");
					user->show_info();
					
					cout << "\n                 :::"
					     << "\n Edit name       [1]"
						 << "\n Edit email      [2]"
						 << "\n Edit phone      [3]\n"

						 << "\n Back            [8]"
						 << "\n Enter           [_]\b\b";
					enter_choice();

					if (choice == '1') user->edit_name();
					else if (choice == '2') user->edit_email();
					else if (choice == '3') user->edit_phone();

					else if (choice == '8') break;
				}
			}
		}
		
		if      (choice == '9') user = nullptr;
		else if (choice == '0') throw(exception("exit"));
	}
}

void Menu::loop()
{
	while (true)
	{
		if      (not tesys.check_admin()) sign_up(true);
		else if (user == nullptr) menu_login();
		
		menu_one();
	}
}

void Menu::save(string file_name)
{
	std::ofstream f_out (file_name, std::ios::binary | std::ios::trunc);
	if (not f_out.is_open()) { cout << " File not open.."; return; }

	tesys.save(f_out);
}
Menu::Menu(string file_name) : tesys(file_name) {}