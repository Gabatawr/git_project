#include "Menu.h"

int main()
{
	string file_name = "save.tesys";
	Menu menu(file_name);
	
	try { menu.loop(); }
	catch (...)
	{
		menu.save(file_name);
		return 0;
	}
}
