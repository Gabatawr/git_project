#pragma once
#include "Car.h";


enum Car_model { tesla, bmw };


class Factory_car;
class Factory
{
	Factory_car* factory_car = nullptr;
	
public:
	Factory(Car_model);
	~Factory();

	Car* operator()(Car_type);
};


class Factory_car
{
public:
	virtual ~Factory_car() = default;

	Car* create(Car_type);

protected:
	virtual Car* new_car(Car_type) = 0;
};


class Factory_tesla : public Factory_car { Car* new_car(Car_type) override; };
class Factory_bmw   : public Factory_car { Car* new_car(Car_type) override; };