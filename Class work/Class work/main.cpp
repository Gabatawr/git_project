#include <iostream>
using std::cout;
using std::cin;

#include "Creator.h"


int main()
{
	Product* product = Creator::create(Product_type::truck);
	product->delivery();

	cout << "\n ";
	system("pause");
}