#pragma once
#include "Task.h"
#include <map>


class SortList
{
protected://---------------------------------------
	std::multimap<std::string, Task*> _storageList;
public://------------------------------------------
	void Print       ();
	bool Filter(std::string key);
	
	void Add         (std::string, Task*);
	void Del         (int id);
};//-----------------------------------------------
