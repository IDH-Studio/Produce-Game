#pragma once
#include "BaseObject.h"


class Factory : public BaseObject
{
public:
	Factory();
	Factory(int number);
	~Factory();
	
	void update(Player* player);
	void render();
	bool canBuy(Player* player, int number);
};