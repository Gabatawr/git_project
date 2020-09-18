#include <iostream>

class ITransport
{
public:
	virtual unsigned get_power() = 0;
	virtual unsigned drive(double) = 0;
	
	virtual ~ITransport() = default;
};

class Car : public ITransport
{
	unsigned power;
	
public:
	Car(unsigned p) : power(p) {}
	unsigned get_power() override { return power; }
	unsigned drive(double km) override { return (km / power) * 60; }
};


class IUpdate : public ITransport
{
protected:
	ITransport* car;
	
public:
	IUpdate(ITransport* T) { car = T; }
};

class Turbo : public IUpdate
{
	double multiplier = 1.2;
	
public:
	Turbo(ITransport* T) : IUpdate(T) {}
	
	unsigned get_power() override { return car->get_power() * multiplier; }
	unsigned drive(double km) override { return (km / get_power()) * 60; }
};

class Nitro : public IUpdate
{
	double multiplier = 1.1;

public:
	Nitro(ITransport* T) : IUpdate(T) {}

	unsigned get_power() override { return car->get_power() * multiplier; }
	unsigned drive(double km) override { return (km / get_power()) * 60; }
};



int main()
{
	unsigned km = 100;

	
	ITransport* car = new Car(100); // default km/h
	std::cout << "\n " << km << "km for " << car->drive(km) << "min [default]\n";
	
	car = new Turbo(car);
	std::cout << "\n " << km << "km for " << car->drive(km) << "min [+Turbo]\n";

	car = new Nitro(car);
	std::cout << "\n " << km << "km for " << car->drive(km) << "min [+Turbo, +Nitro]\n";

	
	std::cout << "\n\n "; system("pause");
}