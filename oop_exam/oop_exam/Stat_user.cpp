#include "Stat_user.h"

#include <iostream>
using std::cout;


void Stat_user::show_stat_sections(string section_name)
{
	if (user_test_list.empty())
	{
		cout << "\n Not found \n\n ";
		system("pause");
	}
	else
	{
		bool section_test = false;
		for (auto& utl : user_test_list)
		{
			if (utl->get_section_name() == section_name)
			{
				utl->show_stat_test();
				section_test = true;
			}
		}
		if (not section_test)
		{
			cout << "\n Not found \n\n ";
			system("pause");
		}
		else
		{
			cout << "\n\n ";
			system("pause");
		}
	}
}

void Stat_user::show_stat_tests()
{
	if (user_test_list.empty())
	{
		cout << "\n Not found \n\n ";
		system("pause");
	}
	else for (auto& utl : user_test_list) utl->show_stat_test();

	cout << "\n\n ";
	system("pause");
}


		