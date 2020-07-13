#include "Factory.h"
#include "setting.h"


Factory::Factory() : money(0), factoryNumber(1), isOperate(false)
{
	fRect.x = 0;
	fRect.y = 0;
	fRect.w = 0;
	fRect.h = 0;
	start = end = 0;
	showMoney = "money: ";
	showNumber = "factory number: ";
}

Factory::Factory(int number) : money(0), factoryNumber(number), isOperate(false)
{
	fRect.x = number * 50 + 10 - 1;
	fRect.y = number * 14 + 4;
	fRect.w = 40;
	fRect.h = 8;
	start = end = 0;
	showMoney = "money: ";
	showNumber = "factory number: ";
}


Factory::~Factory()
{
	isOperate = false;
}

void Factory::operate(int number)
{
	money = 0;
	factoryNumber = number + 1;
	fRect.x = ((number % 3) * 50 + 10) - 1;
	fRect.y = ((number / 3) * 14) + 4;
	fRect.w = 40;
	fRect.h = 8;
	start = clock();
	isOperate = true;
}

void Factory::update()
{
	if (isOperate)
	{
		end = clock();
		if ((float)(end - start) / CLOCKS_PER_SEC >= 2)
		{
			start = clock();
			++money;
		}
	}
}

void Factory::render()
{
	if (isOperate)
	{
		drawRect(fRect);
		writeBuffer(fRect.x + 1, fRect.y + 1, showNumber + std::to_string(factoryNumber));
		writeBuffer(fRect.x + 1, fRect.y + 2, showMoney + std::to_string(money));
	}
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

void factoryOperate(Factory* factory, int number)
{
	factory[number].operate(number);
}
