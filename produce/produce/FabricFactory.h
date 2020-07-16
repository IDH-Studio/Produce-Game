#pragma once
#include "BaseObject.h"

class FabricFactory : public BaseObject
{
public:
	FabricFactory();
	FabricFactory(int number);
	~FabricFactory();

	void update(Player* player);
	void render();
	char canBuy(Player* player);
	char canBuy(Player* player, int number);
};

