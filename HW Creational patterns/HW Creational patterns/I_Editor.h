#pragma once

class I_Editor
{
public:
	static I_Editor* fabricate(const char*); // factory method

	virtual void create()  = 0;
	virtual void open()    = 0;
	virtual void save()    = 0;
	virtual void save_as() = 0;
	virtual void print()   = 0;
	bool close();

	virtual void menu();
	void file_menu();
	
	static char input_char(const char*);
	
	virtual ~I_Editor() = default;
};