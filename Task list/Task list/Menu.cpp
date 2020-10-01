#include "Menu.h"
#include <iostream>
#include <string>


Menu* Menu::_menu = nullptr;
Menu* Menu::Loading(const char* pathFile)
{
	if (_menu == nullptr) return _menu = new Menu(pathFile);
	else return _menu;
}

// -------------------------------------------------------

Menu::Menu(const char* pathFile)
{
	_printMode = TaskBox::Priority;
	
	SaveLoad::PathFile = pathFile;
	_taskBox = new TaskBox;
	_taskBox->Load();
}

Menu::~Menu()
{
	delete _taskBox;
	_menu = nullptr;
}

// -------------------------------------------------------

void Menu::Help()
{
	std::cout
		<< "\n Keys: [-t] by Tag;"
		<< "\n       [-p] by Priority;"
		<< "\n       [-d] by Date;"
		<< "\n"
		<< "\n Commands .: add"
		<< "\n          .: del  #ID"
		<< "\n          .: done #ID"
		<< "\n          .: edit #ID"
		<< "\n          .: completed"
		<< "\n          .: filter '...' -key"
		<< "\n          .: sort by -key"
		<< "\n          .: save"
		<< "\n          .: exit"
		<< "\n\n ";
	
	system("pause");
}

bool Menu::Exit()
{
	std::cout << "\n Exit without saving changes? yes/save/back : ";
	
	std::string userStr;
	std::getline(std::cin, userStr);
	for (auto& ch : userStr) if (ch >= 65 && ch <= 90) ch += 32; // lowercase

	if (FindStr(userStr, "yes")) return true;
	if (FindStr(userStr, "save")) { _taskBox->Save(); return true; }
	
	return false;
}

void Menu::Run()
{
	bool trySearch = false;
	while (true)
	{
		if (not trySearch)
		{
			system("cls");
			_taskBox->Print(_printMode);
		}
		trySearch = false;
		
		std::cout << "\n .: ";

		std::string command;
		std::getline(std::cin, command);
		for (auto& ch : command) if (ch >= 65 && ch <= 90) ch += 32; // lowercase
		
		system("cls");
		if      (FindStr(command, "help"))      { Help(); }
		else if (FindStr(command, "add"))       { _taskBox->Add(); }
		else if (FindStr(command, "del"))       { _taskBox->Del(StrToInt(command)); }
		else if (FindStr(command, "done"))      { _taskBox->Done(StrToInt(command)); }
		else if (FindStr(command, "edit"))      { _taskBox->Edit(StrToInt(command)); }
		else if (FindStr(command, "completed")) { trySearch = _taskBox->Completed(); }
		else if (FindStr(command, "filter"))    { trySearch = _taskBox->Filter(PreFilter(command), command); }
		else if (FindStr(command, "sort"))      { SetPrintMode(command); }
		else if (FindStr(command, "save"))      { _taskBox->Save(); }
		else if (FindStr(command, "exit"))      { if (Exit()) break; }
		else 
		{
			std::cout << "\n Opps, enter 'help' to look commands\n ";
			system("pause");
		}
	}
}

// -------------------------------------------------------

void Menu::SetPrintMode(std::string& command)
{
	TaskBox::Type tmpType = ParseKey(command);
	if (tmpType != TaskBox::Unknown) _printMode = tmpType;
}

bool Menu::FindStr(std::string& command, const char* key)
{
	return command.find(key) != std::string::npos;
}

// -------------------------------------------------------

TaskBox::Type Menu::ParseKey(std::string& command)
{
	if (FindStr(command, "-t")) return TaskBox::Tag;
	if (FindStr(command, "-p")) return TaskBox::Priority; // default
	if (FindStr(command, "-d")) return TaskBox::Date;

	std::cout << "\n Opps, using key: -t -p -d\n ";
	system("pause");
	return TaskBox::Unknown;
}

TaskBox::Type Menu::PreFilter(std::string& command)
{
	TaskBox::Type filterType = ParseKey(command);
	if (filterType == TaskBox::Type::Unknown) return filterType;
	
	char symbol = '\'';
	int start = -1, end = -1;

	for (auto i = 0; i < command.length(); ++i)
	{
		if (command[i] == symbol)
		{
			if (start == -1) start = i;
			else { end = i; break; }
		}
	}

	std::string strTmp;
	if (start != -1 && end != -1)
	{
		strTmp.resize(end - start - 1);
		for (auto i = start + 1; i < end; i++) strTmp[i - (start + 1)] = command[i];
	}

	command = strTmp;
	if (filterType == TaskBox::Date) { FixByDate(command); }
	
	return filterType;
}

// -------------------------------------------------------

void Menu::FixByDate(std::string& date)
{
	int arrTmp[3]{ Menu::StrToInt(date, 1), Menu::StrToInt(date, 2), Menu::StrToInt(date, 3), };
	date = Menu::IntToStr(arrTmp[2]) + '.' + Menu::IntToStr(arrTmp[0]) + '.' + Menu::IntToStr(arrTmp[1]);
}

std::string Menu::IntToStr(int number, bool frontZero)
{
	std::string strTmp;
	int count = 0;

	if (number == 0) count++;
	else for (int tmp = number; tmp > 0; count++) tmp /= 10;

	strTmp.resize((count += (number < 10 && frontZero ? 1 : 0)), '0');

	for (auto i = count - 1; i > -1; i--)
	{
		strTmp[i] = static_cast<char>(number % 10 + 48);
		number /= 10;
	}
	return strTmp;
}

int Menu::StrToInt(std::string& str, int numInRow)
{
	double number = 0;
	for (auto i = 0, count = 0; i < str.length(); ++i)
	{
		bool flag = false;

		int digits = i;
		while (str[i] >= 48 && str[i] <= 57) {
			flag = true;
			++i;
		}
		digits = i - digits;

		if (digits > 0) count++;

		if (count == numInRow)
		{
			i -= digits;
			for (auto j = 0; j < digits; j++, i++)
			{
				number += static_cast<double>(str[i] - 48) / 10;
				number *= 10;
			}
			return static_cast<int>(number);
		}
		if (flag) i--;
	}
	return 0;
}
