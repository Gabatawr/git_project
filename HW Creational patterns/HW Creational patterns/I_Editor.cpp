#include "I_Editor.h"

#include <iostream>
#include "conio.h"

#include "txt_Editor.h"
#include "png_Editor.h"


I_Editor* I_Editor::fabricate(const char* format)
{
	if (format == "txt")  return new txt_Editor();
	if (format == "png")  return new png_Editor();
	
	return nullptr;
}

bool I_Editor::close()
{
	while (true)
	{
		std::cout << "\n Close the file without saving changes?\n"
				<< " y. Yes\n"
				<< " s. Save\n"
				<< " b. Back\n";
		
		char choice = input_char("yYsSbB");
		
		if (choice == 'y' || choice == 'Y') return true;
		if (choice == 's' || choice == 'S')
		{
			save();
			return true;
		}
		if (choice == 'b' || choice == 'B') return false;
	}
}

void I_Editor::menu()
{
	bool work = true;
	while (work)
	{
		std::cout << "\n 1. File menu\n"
					<< " 0. Close\n";
		
		char choice = input_char("10");

		if (choice == '1') file_menu();
		if (choice == '0') work = !close();
	}
	std::cout << "\n Editor closed.\n";
}


void I_Editor::file_menu()
{
	while (true)
	{
		std::cout << "\n 1. Create\n"
					<< " 2. Open\n"
					<< " 3. Save\n"
					<< " 4. Save as\n"
					<< " 5. Print\n"
					<< " b. Back\n";
		
		char choice = input_char("12345bB");

		if (choice == '1') create();
		else if (choice == '2') open();
		else if (choice == '3') save();
		else if (choice == '4') save_as();
		else if (choice == '5') print();
		else if (choice == 'b' || choice == 'B') break;
	}
}

char I_Editor::input_char(const char* white_list)
{
	std::cout << " _\b";
	
	char ch, tmp = ' ';
	unsigned count = 0;

	while ((ch = _getch()) != '\r')
	{
		if (count == 0 && ch != '\b')
		{
			tmp = ' ';
			for (auto i = 0; tmp != '\0'; ++i)
			{
				tmp = white_list[i];
				if (ch == tmp)
				{
					std::cout << ch;
					count++;
					break;
				}
			}
		}
		else if (count == 1 && ch == '\b')
		{
			count--;
			std::cout << ch << '_' << ch;
		}
	}
	
	std::cout << '.' << std::endl;
	
	return tmp;
}