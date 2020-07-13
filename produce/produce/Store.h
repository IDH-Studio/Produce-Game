#pragma once
#include "Player.h"

class Store
{
private:
	int productPrice;
	Player* customer;
	bool isOpen;
public:
	Store();
	~Store();

	void visit(Player* player);
	void sell();
	void out();
};

