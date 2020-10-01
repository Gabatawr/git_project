#include "Task.h"
#include "Menu.h"
#include <iostream>
#include "conio.h"


int Task::IDCounter = 1;

int  Task::GetIDCounter()            { return IDCounter;    }
void Task::SetIDCounter(int counter) { IDCounter = counter; }

// -------------------------------------------------------

Task::Task(std::string& text, std::string& tag, int priority, DateTime* dateTime, int id, bool done)
: _text(text), _tag(tag), _priority(priority), _dateTime(dateTime), _ID(id == 0 ? IDCounter++ : id), _done(done)
{}

Task* Task::GetTask(std::string text,
					std::string tag,
					std::string priority,
					std::string date,
					std::string time,
					std::string id,
					std::string done)
{
	return new Task(text,
					tag,
					Menu::StrToInt(priority),
					new DateTime(date, time),
					Menu::StrToInt(id),
					Menu::StrToInt(done));
}

Task::~Task() { delete _dateTime; }

// -------------------------------------------------------

void Task::Print() const
{
	std::cout
		<< " [" << (_done ? '+' : ' ') << "]\t"
		<< "Tag: " << _tag << "\n\t"
		<< _text << "\n "
		<< "#" << (_ID < 10 ? "0" : "") << _ID << '\t'
		<< "Priority: " << _priority << '\t'
		<< "Date: " << _dateTime->toString(DateTime::Date) << '\t'
		<< "Time: " << _dateTime->toString(DateTime::Time);
}

int Task::GetID() const { return _ID; }

// -------------------------------------------------------

void Task::Edit()
{
	auto TryReplace = [](std::string& oldStr) -> std::string
	{
		char ch;
		int counter = 0;
		std::string strTmp;

		std::cout << oldStr;
		for (auto i = 0; i < oldStr.length(); ++i) std::cout << '\b';
		
		while ((ch = _getch()) != '\r')
		{
			if (ch == '\b' && counter != 0)
			{
				strTmp.pop_back();
				if (--counter == 0)
				{
					std::cout << ch << oldStr;
					for (auto i = 0; i < oldStr.length(); ++i) std::cout << '\b';
				}
				else std::cout << ch << ' ' << ch;
			}
			else if (ch != '\b')
			{
				if (++counter == 1)
				{
					for (auto i = 0; i < oldStr.length(); ++i) std::cout << ' ';
					for (auto i = 0; i < oldStr.length(); ++i) std::cout << '\b';
				}
				strTmp.push_back(ch);
				std::cout << ch;
			}
		}
		
		if (strTmp.empty())strTmp = oldStr;
		else for (auto i = 0; i < strTmp.length(); ++i) std::cout << '\b';
		
		return strTmp;
	};
	
	std::cout << " Task after:\n";
	Print();
	
	std::string tmpStr;
	
	std::cout << "\n\n Task before:\n";
	std::cout << " [" << (_done ? '+' : ' ') << "]\t";
	
	std::cout << "Tag: ";
	std::cout << (_tag = TryReplace(_tag)) << "\n\t";
	
	std::cout << (_text = TryReplace(_text)) << "\n ";
	std::cout << "#" << (_ID < 10 ? "0" : "") << _ID << '\t';
	
	std::cout << "Priority: ";
	std::cout << (_priority = Menu::StrToInt(tmpStr = (TryReplace((tmpStr = Menu::IntToStr(_priority)))))) << '\t';
	
	std::cout << "Date: ";
	_dateTime->Replace((tmpStr = (TryReplace((tmpStr = _dateTime->toString(DateTime::Date))))), DateTime::Date);
	std::cout << _dateTime->toString(DateTime::Date) << '\t';

	std::cout << "Time: ";
	_dateTime->Replace((tmpStr = (TryReplace((tmpStr = _dateTime->toString(DateTime::Time))))), DateTime::Time);
	std::cout << _dateTime->toString(DateTime::Time);
}

void Task::Done() { _done = true; }

bool Task::GetDone() { return _done; }

// -------------------------------------------------------

void Task::Save()
{
	SaveSrt(_text);
	SaveSrt(_tag);
	SaveSrt(Menu::IntToStr(_priority));
	SaveSrt(_dateTime->toString(DateTime::Date));
	SaveSrt(_dateTime->toString(DateTime::Time));
	SaveSrt(Menu::IntToStr(_ID));
	SaveSrt(Menu::IntToStr(_done));
}

void Task::Load() {}
