#include "Creator.h"


Product* Creator::create(Product_type type)
{
	Creator* creator = nullptr;
	Product* product = nullptr;
	
	if      (type == Product_type::truck) { creator = new Creator_Truck; }
	else if (type == Product_type::ship)  { creator = new Creator_Ship; }

	product = creator->new_product();
	
	delete creator;
	return product;
}

Product* Creator_Truck::new_product() { return new Truck; }
Product* Creator_Ship::new_product()  { return new Ship; }