#include "png_Editor.h"

#include <iostream>

void png_Editor::create()
{
	std::cout << "\n Create new 'png' file\n";
}

void png_Editor::open()
{
	std::cout << "\n Open 'png' file\n";
}

void png_Editor::save()
{
	std::cout << "\n Save 'png' file\n";
}

void png_Editor::save_as()
{
	std::cout << "\n Save as 'png' file\n";
}

void png_Editor::print()
{
	std::cout << "\n Print 'png' file\n";
}

void png_Editor::menu()
{
	bool work = true;
	while (work)
	{
		std::cout << "\n 1. File menu\n"
					<< " 2. Image menu\n"
					<< " 0. Close\n";
		
		char choice = input_char("120");

		if (choice == '1') file_menu();
		if (choice == '2') image_menu();
		if (choice == '0') work = !close();
	}
	std::cout << "\n Editor closed.\n";
}

void png_Editor::image_menu()
{
	std::cout << "\n 0. Image menu [prototype]\n";
}
