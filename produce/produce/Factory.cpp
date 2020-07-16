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
	setColor(LIGHT_BLUE);
	writeBuffer(getRect().x, getRect().y,				"========================================");
	writeBuffer(getRect().x, getRect().y + 1,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 2,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 3,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 4,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 5,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 6,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 7,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + getRect().h, "========================================");
	
	setColor(WHITE);
	writeBuffer(getRect().x + 1, getRect().y + 1, getShowNumber() + std::to_string(getNumber()));

	if (checkActivate())
	{
		writeBuffer(getRect().x + 1, getRect().y + 2, getShowProduct() + std::to_string(getProduct()));
	}
	else
	{
		setColor(LIGHT_RED);
		writeBuffer(getRect().x + 1, getRect().y + 2, "need - money: " + std::to_string(objectCost.factoryCost));
	}
}

char Factory::canBuy(Player* player)
{
	if (checkActivate())
	{
		return CANT_OPEN;
	}
	else
	{
		if (player->getMoney() >= objectCost.factoryCost)
		{
			player->giveMoney(objectCost.factoryCost);
			active();
			objectCost.factoryCost += static_cast<unsigned short>(objectCost.factoryCost * 0.25);
			return CAN_OPEN;
		}
		else
		{
			return CANT_BUY;
		}
	}
}

char Factory::canBuy(Player* player, int number)
{
	if (checkActivate())
	{
		return CANT_OPEN;
	}
	else
	{
		if (player->getMoney() >= objectCost.factoryCost)
		{
			player->giveMoney(objectCost.factoryCost);
			active(number);
			objectCost.factoryCost += static_cast<unsigned short>(objectCost.factoryCost * 0.25);
			return CAN_OPEN;
		}
		else
		{
			return CANT_BUY;
		}
	}
}