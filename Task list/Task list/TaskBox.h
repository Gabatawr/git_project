#pragma once
#include "SaveLoad.h"
#include "SortList.h"
#include <list>


class TaskBox : public SaveLoad
{//--------------------------------------------------
public:  enum Type { Tag, Priority, Date, Unknown };
private://-------------------------------------------
         SortList*        _sortList[3];
         std::list<Task*> _taskList;
public://--------------------------------------------
         TaskBox ();
	
    void Print   (Type sortType);
    bool Filter  (Type filterType, std::string& key);
	
    void Add     ();
    void Del     (int id);
    void Edit    (int id);
    void Done    (int id);
	
    void Save    () override;
    void Load    () override;
	
        ~TaskBox () override;
};//-------------------------------------------------

