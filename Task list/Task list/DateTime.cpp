#include "Menu.h"
#include "DateTime.h"
#include <iostream>


DateTime::DateTime() : _month(0), _day(0), _year(0), _hour(0), _min(0) {}

DateTime::DateTime(std::string date, std::string time) : DateTime()
{
	Replace(date, Date);
	Replace(time, Time);
}

// -------------------------------------------------------

bool DateTime::Replace(std::string& userDate, Type type)
{
	int size = type == Date ? 3 : 2;
	int* arrNum = new int[size];

	for (auto i = 0; i < size; ++i)
	{
		if ((arrNum[i] = Menu::StrToInt(userDate, i + 1)) == 0)
		{
			delete[] arrNum;
			return false;
		}
	}
	
	int check = 0;
	do {
		if (type == Date)
		{
			std::swap(_month, arrNum[0]);
			std::swap(_day, arrNum[1]);
			std::swap(_year, arrNum[2]);
		}
		else
		{
			std::swap(_hour, arrNum[0]);
			std::swap(_min, arrNum[1]);
		}
		
		++check;
	} while (not Check(type));
	
	delete[] arrNum;
	return check == 1;
}

bool DateTime::Check(Type type) const
{
	if (type == Date)
	{
		if (_month > 12 || _month < 1) return false;
		if (_day > 31 || _day < 1) return false;

		if (_day == 31 && (_month != 1 && _month != 2 && _month != 3 && _month != 5 && _month != 7 && _month != 8 && _month != 10 && _month != 12)) return false;

		auto isLeapYear = [&]() { return _year % 4 != 0 || _year % 100 == 0 && _year % 400 != 0; };
		if (_day > 28 && (_month == 2 && not isLeapYear()) || _day > 29 && (_month == 2 && isLeapYear())) return false;
	}
	else
	{
		if (_hour > 23 || _hour < 0) return false;
		if (_min > 59 || _min < 0) return false;
	}
	
	return true;
}

// -------------------------------------------------------

std::string DateTime::toString(Type type) const
{
	std::string ret;
	
	if (type == Date) return ret = Menu::IntToStr(_month, true) + '.' + Menu::IntToStr(_day, true) + '.' + Menu::IntToStr(_year, true);
	else              return ret = Menu::IntToStr(_hour, true)  + ':' + Menu::IntToStr(_min, true);
}
