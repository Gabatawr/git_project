#pragma once
#include <string>

class DateTime
{//----------------------------------------------------------
public: enum Type { Date, Time };
private://---------------------------------------------------
	int _month;
	int _day;
	int _year;

	int _hour;
	int _min;
	
private://---------------------------------------------------
	    bool        Check    (Type) const;
public://----------------------------------------------------
	                DateTime ();
	                DateTime (std::string, std::string = "");
	
	    bool        Replace  (std::string&, Type);
        std::string toString (Type) const;
};//---------------------------------------------------------

