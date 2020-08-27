#pragma once

class Product
{
public:
	virtual ~Product() = default;

	virtual void delivery();
};

class Truck : public Product { public: virtual void delivery() override; };
class Ship  : public Product { public: virtual void delivery() override; };