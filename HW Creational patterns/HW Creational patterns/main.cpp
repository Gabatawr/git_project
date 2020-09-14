#include <iostream>
#include "I_Editor.h"

int main()
{
    I_Editor* txt = I_Editor::fabricate("txt");
	I_Editor* png = I_Editor::fabricate("png");

	std::cout << "\n txt menu:";
	txt->menu();

	std::cout << "\n png menu:";
	png->menu();
}