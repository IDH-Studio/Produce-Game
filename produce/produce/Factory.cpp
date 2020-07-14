#include "Factory.h"
#include "setting.h"


void Factory::setShowProduct(std::string productName)
{
	showProduct = productName;
}

void Factory::addProduct()
{
	++product;
}

clock_t Factory::getStart()
{
	return start;
}

clock_t Factory::getEnd()
{
	return end;
}

void Factory::setStart()
{
	start = clock();
}

void Factory::setEnd()
{
	end = clock();
}


Factory::Factory() : product(0), factoryNumber(1), isOperate(false)
{
	fRect.x = factoryNumber * 50 + 10 - 1;
	fRect.y = factoryNumber * 14 + 4;
	fRect.w = 40;
	fRect.h = 8;
	start = end = 0;
	showProduct = "product: ";
	showNumber = "factory number: ";
}

Factory::Factory(int number) : product(0), factoryNumber(number), isOperate(false)
{
	fRect.x = number * 50 + 10 - 1;
	fRect.y = number * 14 + 4;
	fRect.w = 40;
	fRect.h = 8;
	start = end = 0;
	showProduct = "product: ";
	showNumber = "factory number: ";
}


Factory::~Factory()
{
	isOperate = false;
}

void Factory::operate(int number)
{
	product = 0;
	factoryNumber = number + 1;
	fRect.x = ((number % 3) * 50 + 10) - 1;
	fRect.y = ((number / 3) * 14) + 4;
	fRect.w = 40;
	fRect.h = 8;
	start = clock();
	isOperate = true;
}

void Factory::close(int number)
{
	isOperate = false;
}

void Factory::update(Player* player)
{
	if (isOperate)
	{
		end = clock();
		if ((float)(end - start) / CLOCKS_PER_SEC >= 2)
		{
			start = clock();
			++product;
			player->addProduct();
		}
	}
}

void Factory::render()
{
	if (isOperate)
	{
		// border
		writeBuffer(fRect.x, fRect.y,			"========================================");
		writeBuffer(fRect.x, fRect.y + 1,		"|                                      |");
		writeBuffer(fRect.x, fRect.y + 2,		"|                                      |");
		writeBuffer(fRect.x, fRect.y + 3,		"|                                      |");
		writeBuffer(fRect.x, fRect.y + 4,		"|                                      |");
		writeBuffer(fRect.x, fRect.y + 5,		"|                                      |");
		writeBuffer(fRect.x, fRect.y + 6,		"|                                      |");
		writeBuffer(fRect.x, fRect.y + 7,		"|                                      |");
		writeBuffer(fRect.x, fRect.y + fRect.h, "========================================");
		
		writeBuffer(fRect.x + 1, fRect.y + 1, showNumber + std::to_string(factoryNumber));
		writeBuffer(fRect.x + 1, fRect.y + 2, showProduct + std::to_string(product));
	}
}

bool Factory::isOperated()
{
	return isOperate;
}

int Factory::getProduct()
{
	return product;
}

int Factory::getFactoryNumber()
{
	return factoryNumber;
}


bool factoryOperate(Factory* factory, int number)
{
	if (factory[number].isOperated())
	{
		return false;
	}
	else
	{
		factory[number].operate(number);
		return true;
	}
}


bool factoryClose(Factory* factory, int number)
{
	if (factory[number].isOperated())
	{
		factory[number].close(number);
		return true;
	}
	else
	{
		return false;
	}
}