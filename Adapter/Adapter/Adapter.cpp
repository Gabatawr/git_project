#include <iostream>

class I_Transport
{
public:
	virtual void drive() = 0;
};

class Car : public I_Transport
{
public:
	void drive() override
	{
		std::cout << "Car drive\n";
	}
};

class Ship
{
public:
	void sail()
	{
		std::cout << "Ship sail\n";
	}
};

class Ship_to_transport : public I_Transport
{
	Ship* ship;
public:
	Ship_to_transport(Ship* s) : ship(s) {}
	void drive() override
	{
		ship->sail();
	}
};

class Driver
{
public:
	void travel(I_Transport* t)
	{
		t->drive();
	}
};



int main()
{
	Driver driver;
	
	auto* car = new Car;
	driver.travel(car);

	auto* ship = new Ship;
	auto* ship_adapt = new Ship_to_transport(ship);
	driver.travel(ship_adapt);

	system("pause");
}

