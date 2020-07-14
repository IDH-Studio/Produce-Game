#include "BaseObject.h"
#include "setting.h"


// constructor, destructor
BaseObject::BaseObject() : product(0), objectNumber(1), isActivate(false)
{
	rect.x = 50 + 10 - 1;
	rect.y = 14 + 4;
	rect.w = 40;
	rect.h = 8;
	lastTime = curTime = 0;
	showProduct = "product: ";
	showNumber = "number: ";
}


BaseObject::BaseObject(int number) : product(0), objectNumber(number), isActivate(false)
{
	rect.x = ((number % 3) * 50 + 10) - 1;
	rect.y = ((number / 3) * 14) + 4;
	rect.w = 40;
	rect.h = 8;
	lastTime = curTime = 0;
	showProduct = "product: ";
	showNumber = "number: ";
}


BaseObject::~BaseObject()
{
	isActivate = false;
}


// protected functions
void BaseObject::setShowProduct(std::string productName)
{
	showProduct = productName + ": ";
}

void BaseObject::setWhatNumber(std::string whatNumber)
{
	showNumber.insert(0, whatNumber);
}

void BaseObject::addProduct()
{
	++product;
}

clock_t BaseObject::getCurTime()
{
	return curTime;
}

void BaseObject::setCurTime()
{
	curTime = clock();
}

clock_t BaseObject::getLastTime()
{
	return lastTime;
}

void BaseObject::setLastTime()
{
	lastTime = clock();
}

OBJECT_RECT BaseObject::getRect()
{
	return rect;
}

std::string BaseObject::getShowNumber()
{
	return showNumber;
}

std::string BaseObject::getShowProduct()
{
	return showProduct;
}


// public functions
void BaseObject::active(int number)
{
	product = 0;
	objectNumber = number;
	rect.x = ((number % 3) * 50 + 10) - 1;
	rect.y = ((number / 3) * 14) + 4;
	rect.w = 40;
	rect.h = 8;
	lastTime = clock();
	isActivate = true;
}

bool BaseObject::close()
{
	if (isActivate)
	{
		isActivate = false;
		return true;
	}
	else
	{
		return false;
	}
}

void BaseObject::update(Player* player)
{
	if (isActivate)
	{
		curTime = clock();
		if (static_cast<float>(curTime - lastTime) / CLOCKS_PER_SEC >= 2)
		{
			lastTime = clock();
			++product;
			player->addProduct();
		}
	}
}

void BaseObject::render()
{
	//// border
	//writeBuffer(rect.x, rect.y,			 "========================================");
	//writeBuffer(rect.x, rect.y + 1,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 2,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 3,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 4,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 5,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 6,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 7,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + rect.h, "========================================");

	//if (isActivate)
	//{
	//	writeBuffer(rect.x + 1, rect.y + 1, showNumber + std::to_string(objectNumber));
	//	writeBuffer(rect.x + 1, rect.y + 2, showProduct + std::to_string(product));
	//}
	//else
	//{
	//	
	//}
}

bool BaseObject::canBuy(Player* player, int number)
{
	/*
	if (player->getMoney() >= objectCost.factoryCost)
	{
		player->setMoney(objectCost.factoryCost);
		active(number);
		return true;
	}
	else
	{
		return false;
	}
	*/
}

// getter
bool BaseObject::checkActivate()
{
	return isActivate;
}


int BaseObject::getProduct()
{
	return product;
}

int BaseObject::getNumber()
{
	return objectNumber;
}