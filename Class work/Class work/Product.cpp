#include "Product.h"
#include <iostream>

void Product::delivery() { std::cout << "\n Base Delivery\n"; }

void Truck::delivery()   { std::cout << "\n Truck Delivery\n"; }
void Ship::delivery()    { std::cout << "\n Ship Delivery\n"; }