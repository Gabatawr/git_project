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


class IUpdate : public ITransport // Decorator
{
protected:
	ITransport* car;
	double multiplier;
	
public:
	IUpdate(ITransport* T, double M) : car(T), multiplier(M) {}

	unsigned get_power() override { return car->get_power() * multiplier; }
	unsigned drive(double km) override { return (km / get_power()) * 60; }
};

class Turbo : public IUpdate
{
public:
	Turbo(ITransport* T) : IUpdate(T, 1.2) {}
};

class Nitro : public IUpdate
{
public:
	Nitro(ITransport* T) : IUpdate(T, 1.1) {}
};



int main()
{
	unsigned km = 100;

	
	ITransport* car = new Car(100); // default power (km/h)
	std::cout << "\n " << km << "km for " << car->drive(km) << "min [default]\n";
	// 100km for 60min [default]
	
	car = new Turbo(car); // car power = power * 1.2
	std::cout << "\n " << km << "km for " << car->drive(km) << "min [+Turbo]\n";
	// 100km for 50min [+Turbo]

	car = new Nitro(car);
	std::cout << "\n " << km << "km for " << car->drive(km) << "min [+Turbo, +Nitro]\n";
	// 100km for 45min [+Turbo, +Nitro]

	
	std::cout << "\n\n "; system("pause");
}