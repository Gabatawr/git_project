#include "TaskBox.h"
#include "Menu.h"
#include <iostream>
#include <ctime>


TaskBox::TaskBox()  { for (auto i = 0; i < 3; ++i) _sortList[i] = new SortList; }
TaskBox::~TaskBox() { for (auto i = 0; i < 3; ++i) delete _sortList[i]; }

// -------------------------------------------------------

void TaskBox::Print(Type sortType)
{
	_sortList[sortType]->Print();
}

bool TaskBox::Filter(Type filterType, std::string& key)
{
	if (filterType == Unknown) return false;
	if (key.empty())
	{
		std::cout << "\n Empty search field, using ''\n ";
		system("pause");
		return false;
	}
	
	return _sortList[filterType]->Filter(key);
}

// -------------------------------------------------------

void TaskBox::Add()
{
	auto GetStr = [](const char* txt, const char* format = ": ") -> std::string
	{
		std::string strTmp;
		std::cout << "       " << txt << format;
		std::getline(std::cin, strTmp);
		return strTmp;
	};

	auto CheckDate = [](std::string& strDate)
	{
		DateTime* checkDate = new DateTime(strDate);
		if (checkDate->toString(DateTime::Date) == "00.00.00")
		{
			time_t seconds = time(0);
			tm* timeinfo = new tm;
			localtime_s(timeinfo, &seconds);
			int month = timeinfo->tm_mon + 1, day = timeinfo->tm_mday, year = timeinfo->tm_year + 1900;

			strDate = Menu::IntToStr(month) + '.' + Menu::IntToStr(day) + '.' + Menu::IntToStr(year);

			delete timeinfo;
		} delete checkDate;
	};

	std::cout << "\n Enter:\n";
	
	std::string text;
	while (text.empty())
	{
		text = GetStr("text");
		if (text.empty()) std::cout << "\n The text of the task is required!";
	}
	
	std::string tag         = GetStr("tag");
	std::string strPriority = GetStr("priority");
	std::string strDate     = GetStr("date", "(default today): mm.dd.yyyy\b\b\b\b\b\b\b\b\b\b");
	CheckDate(strDate);
	std::string strTime     = GetStr("time", "(default 00:00): hh:mm\b\b\b\b\b");
	
	Task* newTask = Task::GetTask(text, tag, strPriority, strDate, strTime);
	_taskList.push_back(newTask);

	_sortList[Tag]->      Add(tag,         newTask);
	_sortList[Priority]-> Add(strPriority, newTask);

	Menu::FixByDate(strDate);
	
	_sortList[Date]->     Add(strDate,     newTask);
}

void TaskBox::Del(int id)
{
	for (auto& sl : _sortList) sl->Del(id);
	
	for (auto it = _taskList.begin(); it != _taskList.end(); ++it)
	{
		if ((*it)->GetID() == id)
		{
			delete (*it);
			_taskList.erase(it);
			break;
		}
	}
}

// -------------------------------------------------------

void TaskBox::Edit(int id)
{
	for (auto& it : _taskList)
	{
		if (it->GetID() == id)
		{
			it->Edit();
			break;
		}
	}
}

void TaskBox::Done(int id)
{
	for (auto& it : _taskList)
	{
		if (it->GetID() == id)
		{
			it->Done();
			break;
		}
	}
}

// -------------------------------------------------------

void TaskBox::Save()
{
	Open(Out);

	if (FileOut->is_open())
	{
		SaveInt(Task::GetIDCounter());
	
		SaveInt(_taskList.size());
		for (auto& it : _taskList) it->Save();
	}
		
	Close(Out);
}

void TaskBox::Load()
{
	Open(In);

	if (FileIn->is_open())
	{
		Task::SetIDCounter(LoadInt());
	
		int listSize = LoadInt();
		for (auto i = 0; i < listSize; ++i)
		{
			enum tmpStr { text, tag, priority, date, time, id, done };
	
			std::string listStr[7];	
			for (auto i = 0; i < 7; ++i) listStr[i] = LoadSrt();
			
			Task* newTask = Task::GetTask(listStr[text], listStr[tag], listStr[priority],
				                          listStr[date], listStr[time],
				                          listStr[id], listStr[done]);
			_taskList.push_back(newTask);

			Menu::FixByDate(listStr[date]);
			for (auto i = 0; i < 3; ++i) _sortList[i]->Add(listStr[i + 1], newTask);
		}
	}
		
	Close(In);
}
