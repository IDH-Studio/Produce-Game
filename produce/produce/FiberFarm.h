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
	bool canBuy(Player* player, int number);
};