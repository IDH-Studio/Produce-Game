#include "Factory.h"
#include "setting.h"


Factory::Factory() : product(0), factoryNumber(1), isOperate(false)
{
	fRect.x = 0;
	fRect.y = 0;
	fRect.w = 0;
	fRect.h = 0;
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

void Factory::update()
{
	if (isOperate)
	{
		end = clock();
		if ((float)(end - start) / CLOCKS_PER_SEC >= 2)
		{
			start = clock();
			++product;
		}
	}
}

void Factory::render()
{
	if (isOperate)
	{
		drawRect(fRect);
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


void drawRect(MY_RECT rect)
{
	// Top
	for (int i = 0; i < rect.w; i++)
	{
		writeBuffer(rect.x + i, rect.y, "=");
	}

	// Bottom
	for (int i = 0; i < rect.w; i++)
	{
		writeBuffer(rect.x + i, rect.y + rect.h, "=");
	}

	// Left
	for (int i = 0; i < rect.h; i++)
	{
		writeBuffer(rect.x, rect.y + i, "|");
	}

	// Right
	for (int i = 0; i < rect.h; i++)
	{
		writeBuffer(rect.x + rect.w, rect.y + i, "|");
	}
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