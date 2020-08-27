#include "Factory.h"

Factory::Factory(Car_model car_model)
{
	if      (car_model == Car_model::tesla) factory_car = new Factory_tesla;
	else if (car_model == Car_model::bmw)   factory_car = new Factory_bmw;
}

Factory::~Factory() { delete factory_car; }

Car* Factory::operator()(Car_type car_type) { return factory_car->create(car_type); }


Car* Factory_car::create(Car_type car_type) { return new_car(car_type); }

Car* Factory_tesla::new_car(Car_type car_type)
{
	if      (car_type == Car_type::pickup) return new Car(car_type, "Tesla-P-Engine", "Tesla-P-Transmission");
	else if (car_type == Car_type::sedan)  return new Car(car_type, "Tesla-S-Engine", "Tesla-S-Transmission");
	else if (car_type == Car_type::truck)  return new Car(car_type, "Tesla-T-Engine", "Tesla-T-Transmission");

	return nullptr;
}

Car* Factory_bmw::new_car(Car_type car_type)
{
	if      (car_type == Car_type::pickup) return new Car(car_type, "BMW-P-Engine", "BMW-P-Transmission");
	else if (car_type == Car_type::sedan)  return new Car(car_type, "BMW-S-Engine", "BMW-S-Transmission");
	else if (car_type == Car_type::truck)  return new Car(car_type, "BMW-T-Engine", "BMW-T-Transmission");

	return nullptr;
}