#pragma once
#include "SaveLoad.h"
#include "DateTime.h"


class Task : public SaveLoad
{
private://----------------------------------------------------------------------------
	static int          IDCounter;
	
           std::string _text;
	       std::string _tag;
	
	       int         _priority;
	       DateTime*   _dateTime;

	       int         _ID;
	       bool        _done;
private://----------------------------------------------------------------------------
	             Task         (std::string& text, std::string& tag,
			                   int priority, DateTime* dateTime,
					           int id = 0, bool done = false);
public://-----------------------------------------------------------------------------
	static Task* GetTask      (std::string text, std::string tag,
		                       std::string priority, std::string date, std::string time,
		                       std::string  id = "", std::string  done = "");

	static int   GetIDCounter ();
	static void  SetIDCounter (int);
	       int   GetID        () const;
	
	       void  Print        () const;
	       
	       void  Edit         ();
	       void  Done         ();

	       void  Save         () override;
	       void  Load         () override;

		        ~Task         () override;
};//----------------------------------------------------------------------------------

