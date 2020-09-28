#include "SortList.h"
#include <iostream>


void SortList::Print()
{
	for (auto it = _storageList.begin(); it != _storageList.end(); ++it)
	{
		it->second->Print();
		std::cout << "\n\n";
	}
}

bool SortList::Filter(std::string key)
{
	auto itFirst = _storageList.lower_bound(key);
	auto itLast = _storageList.upper_bound(key);
	
	if (itFirst != _storageList.end())
	{
		for (auto it = itFirst; it != itLast; ++it)
		{
			it->second->Print();
			std::cout << "\n\n";
		}
	}
	
	else 
	{
		std::cout << "\n Not found\n ";
		system("pause");
		return false;
	}

	return true;
}

// -------------------------------------------------------

void SortList::Add(std::string sortField, Task* task)
{
	_storageList.emplace(sortField, task);
}

void SortList::Del(int id)
{
	for (auto it = _storageList.begin(); it != _storageList.end(); ++it)
	{
		if (it->second->GetID() == id)
		{
			_storageList.erase(it);
			break;
		}
	}
}
