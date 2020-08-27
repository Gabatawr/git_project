#pragma once
#include <string>
using std::string;


enum Car_type { truck, sedan, pickup };


class Engine;
class Transmission;


class Car
{
public:
	Car(Car_type, string, string);
	~Car();
	
	void info() const;
	
protected:
	Car_type type;

	Engine* engine;
	Transmission* transmission;
};


class Engine
{
	string engine_type;
	
public:
	Engine(string&);
	string get_type() const;
};

class Transmission
{
	string transmission_type;
	
public:
	Transmission(string&);
	string get_type() const;
};
