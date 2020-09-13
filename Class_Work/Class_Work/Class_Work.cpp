#include <iostream>


class Template_method
{
public:
	void build_house(int num_floor = 3)
	{
		build_foor();
		build_floor(num_floor);
		build_foundation();
		build_pool();
	}
	virtual void build_foor() = 0;
	virtual void build_floor(int) = 0;
	virtual void build_foundation() = 0;
	virtual void build_pool(){};
};

class Hotel_poll : public Template_method
{
public:
	void build_foor() override
	{
		std::cout << "/=HOTEL=\\\n";
	}
	void build_floor(int num_floor) override
	{
		for (auto i = 0; i < num_floor; i++)
		{
			std::cout << "|=O=O=O=|\n";
		}
	}
	void build_foundation() override
	{
		std::cout << "|xx[ ]xx|\n";
	}
	void build_pool() override
	{
		std::cout << "[~~~~~~~]\n";
	}
};

class Motel : public Template_method
{
public:
	void build_foor() override
	{
		std::cout << "/=MOTEL=\\\n";
	}
	void build_floor(int num_floor) override
	{
		for (auto i = 0; i < num_floor; i++)
		{
			std::cout << "|=Q=Q=Q=|\n";
		}
	}
	void build_foundation() override
	{
		std::cout << "|dd[ ]bb|\n";
	}
};

int main()
{
	Hotel_poll house;
	house.build_house(5);

	std::cout << "\n\n\n";
	
	Motel house2;
	house2.build_house(3);
}