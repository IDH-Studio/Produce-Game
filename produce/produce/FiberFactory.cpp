#include "FiberFactory.h"



FiberFactory::FiberFactory()
{
	setShowProduct("fiber: ");
}

FiberFactory::FiberFactory(int number) : Factory(number)
{
	setShowProduct("fiber: ");
}


FiberFactory::~FiberFactory()
{

}

void FiberFactory::update(Player* player)
{
	if (isOperated())
	{
		setEnd();
		if ((float)(getEnd() - getStart()) / CLOCKS_PER_SEC >= 2)
		{
			setStart();
			addProduct();
			player->addFiber();
		}
	}
}


bool factoryOperate(FiberFactory* factory, int number)
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


bool factoryClose(FiberFactory* factory, int number)
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