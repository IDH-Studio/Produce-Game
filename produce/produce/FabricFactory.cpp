#include "FabricFactory.h"
#include "setting.h"



FabricFactory::FabricFactory()
{
	setWhatNumber("Fabric Factory ");
}


FabricFactory::FabricFactory(int number) : BaseObject(number)
{
	setWhatNumber("Fabric Factory ");
}


FabricFactory::~FabricFactory()
{

}

void FabricFactory::update(Player * player)
{
	if (checkActivate())
	{
		setCurTime();
		if (static_cast<float>(getCurTime() - getLastTime()) / CLOCKS_PER_SEC >= 2)
		{
			setLastTime();
			addProduct();
			player->addFabric();
		}
	}
}

void FabricFactory::render()
{
	// border
	setColor(LIGHT_GREEN);
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
		writeBuffer(getRect().x + 1, getRect().y + 2, "need -> money: " + 
			std::to_string(objectCost.fabricCost.money) + ", " + "fiber: " +
			std::to_string(objectCost.fabricCost.fiber));
	}
}

char FabricFactory::canBuy(Player * player)
{
	if (checkActivate())
	{
		return CANT_OPEN;
	}
	else
	{
		if (player->getMoney() >= objectCost.fabricCost.money && player->getFiber() >= objectCost.fabricCost.fiber)
		{
			player->giveMoney(objectCost.fabricCost.money);
			player->giveFabric(objectCost.fabricCost.fiber);
			active();
			objectCost.fabricCost.money += static_cast<unsigned short>(objectCost.fabricCost.money * 0.25);
			objectCost.fabricCost.fiber += static_cast<unsigned short>(objectCost.fabricCost.fiber * 0.25);
			return CAN_OPEN;
		}
		else
		{
			if (player->getMoney() < objectCost.fabricCost.money)
			{
				setErrorMessage("buy", "돈이 부족합니다.\n돈이나 더 모아오세요.");
			}
			else if (player->getFiber() < objectCost.fabricCost.fiber)
			{
				setErrorMessage("buy", "섬유가 부족합니다.\n섬유나 모아오세요.");
			}
			return CANT_BUY;
		}
	}
}