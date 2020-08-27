#pragma once
#include "Product.h"


enum Product_type { truck, ship };

class Creator
{
public:
	virtual ~Creator() = default;

	static Product* create(Product_type);
	
protected:
	virtual Product* new_product() = 0;
};

class Creator_Truck : public Creator { Product* new_product() override; };
class Creator_Ship  : public Creator { Product* new_product() override; };