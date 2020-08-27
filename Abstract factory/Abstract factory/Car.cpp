#include "Car.h"

#include <iostream>

Car::Car(Car_type type, string engine_type, string transmission_type)
: type(type), engine(new Engine(engine_type)), transmission(new Transmission(transmission_type)) 
{/**/}

Car::~Car()
{
	delete engine;
	delete transmission;
}

void Car::info() const { std::cout << "\n " << engine->get_type() << "\n " << transmission->get_type() << "\n"; }

Engine::Engine(string& engine_type) : engine_type(engine_type) {}
string Engine::get_type() const { return engine_type; }

Transmission::Transmission(string& transmission_type) : transmission_type(transmission_type) {}
string Transmission::get_type() const { return transmission_type; }
