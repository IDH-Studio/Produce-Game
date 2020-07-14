#pragma once
#include "Factory.h"


class FiberFactory : public Factory
{
public:
	FiberFactory();
	FiberFactory(int number);
	~FiberFactory();

	void update(Player* player);
};


bool factoryOperate(FiberFactory* factory, int number);
bool factoryClose(FiberFactory* factory, int number);