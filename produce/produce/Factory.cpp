#include "Factory.h"
#include "setting.h"

Factory::Factory()
{
	setWhatNumber("factory ");
}

Factory::Factory(int number) : BaseObject(number)
{
	setWhatNumber("factory ");
}


Factory::~Factory()
{
	
}

void Factory::update(Player* player)
{
	if (checkActivate())
	{
		setCurTime();
		if (static_cast<float>(getCurTime() - getLastTime()) / CLOCKS_PER_SEC >= 2)
		{
			setLastTime();
			addProduct();
			player->addProduct();
		}
	}
}

void Factory::render()
{
	// border
	writeBuffer(getRect().x, getRect().y,				"========================================");
	writeBuffer(getRect().x, getRect().y + 1,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 2,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 3,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 4,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 5,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 6,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 7,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + getRect().h, "========================================");

	if (checkActivate())
	{
		writeBuffer(getRect().x + 1, getRect().y + 1, getShowNumber() + std::to_string(getNumber()));
		writeBuffer(getRect().x + 1, getRect().y + 2, getShowProduct() + std::to_string(getProduct()));
	}
	else
	{
		writeBuffer(getRect().x + 1, getRect().y + 1, "buy: " + std::to_string(objectCost.factoryCost));
	}
}

bool Factory::canBuy(Player* player, int number)
{
	if (player->getMoney() >= objectCost.factoryCost)
	{
		player->giveMoney(objectCost.factoryCost);
		active(number);
		objectCost.factoryCost += static_cast<unsigned short>(objectCost.factoryCost * 0.25);
		return true;
	}
	else
	{
		return false;
	}
}