#include <iostream>

#include "Factory.h"
using std::cout;
using std::cin;


int main()
{
	Factory Giga_factory(Car_model::tesla);
	Factory Mega_factory(Car_model::bmw);

	
	Car* car_a = Giga_factory(Car_type::sedan);
	Car* car_b = Mega_factory(Car_type::sedan);


	car_a->info();
	car_b->info();

	cout << "\n ";
	system("pause");
}