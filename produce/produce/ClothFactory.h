#pragma once
#include "BaseObject.h"

class ClothFactory : public BaseObject
{
private:
	int clothAmount;
	float createTime;
public:
	ClothFactory();
	ClothFactory(int number);
	~ClothFactory();

	void update(Player* player);
	void render();
	char canBuy(Player* player);
};

