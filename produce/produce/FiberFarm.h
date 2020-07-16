#pragma once
#include "BaseObject.h"

class FiberFarm : public BaseObject
{
public:
	FiberFarm();
	FiberFarm(int number);
	~FiberFarm();

	void update(Player* player);
	void render();
	char canBuy(Player* player);
	char canBuy(Player* player, int number);
};