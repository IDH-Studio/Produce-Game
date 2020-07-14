#include "FiberFarm.h"
#include "setting.h"



FiberFarm::FiberFarm()
{
	setShowProduct("fiber: ");
	setWhatNumber("fiber farm ");
}


FiberFarm::FiberFarm(int number) : BaseObject(number)
{
	setShowProduct("fiber: ");
	setWhatNumber("fiber farm ");
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
		writeBuffer(getRect().x + 1, getRect().y + 1, "buy: " + std::to_string(objectCost.fiberCost));
	}
}

bool FiberFarm::canBuy(Player* player, int number)
{
	if (player->getMoney() >= objectCost.fiberCost)
	{
		player->giveMoney(objectCost.fiberCost);
		active(number);
		objectCost.fiberCost += (objectCost.fiberCost * 0.25);
		return true;
	}
	else
	{
		return false;
	}
}