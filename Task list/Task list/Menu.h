#pragma once
#include "TaskBox.h"

class Menu
{
private://--------------------------------------------------------------------
	static Menu*         _menu;
	       TaskBox*      _taskBox;
	       TaskBox::Type _printMode;
private://--------------------------------------------------------------------
	                     Menu         (const char* pathFile);
	
	       void          Help         ();
		   void          SetPrintMode (std::string& command);
	
	       TaskBox::Type PreFilter    (std::string& command);
	
	       TaskBox::Type ParseKey     (std::string& command);
	       bool          FindStr      (std::string& command, const char* key);

		   bool          Exit         ();
public://---------------------------------------------------------------------
	static Menu*         Loading      (const char* pathFile);
	       void          Run          ();

	static void          FixByDate    (std::string& date);
	static std::string   IntToStr     (int number, bool frontZero = false);
	static int           StrToInt     (std::string& str, int numInRow = 1);
	
	                    ~Menu         ();
};//--------------------------------------------------------------------------
