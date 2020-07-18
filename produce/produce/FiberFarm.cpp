#include "FiberFarm.h"
#include "setting.h"



FiberFarm::FiberFarm()
{
	setShowProduct("Fiber: ");
	setWhatNumber("Fiber Farm ");
}


FiberFarm::FiberFarm(int number) : BaseObject(number)
{
	setShowProduct("Fiber: ");
	setWhatNumber("Fiber Farm ");
}


FiberFarm::~FiberFarm()
{

}

void FiberFarm::update(Player* player)
{
	if (checkActivate())
	{
		setCurTime();
		if (static_cast<float>(getCurTime() - getLastTime()) / CLOCKS_PER_SEC >= 2)
		{
			setLastTime();
			addProduct();
			player->addFiber();
		}
	}
}

void FiberFarm::render()
{
	// border
	setColor(GREEN);
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
		writeBuffer(getRect().x + 1, getRect().y + 2, "need -> money: " + std::to_string(objectCost.fiberCost));
	}
}

char FiberFarm::canBuy(Player* player)
{
	if (checkActivate())
	{
		return CANT_OPEN;
	}
	else
	{
		if (player->getMoney() >= objectCost.fiberCost)
		{
			player->giveMoney(objectCost.fiberCost);
			active();
			objectCost.fiberCost += static_cast<unsigned short>(objectCost.fiberCost * 0.25);
			return CAN_OPEN;
		}
		else
		{
			return CANT_BUY;
		}
	}
}