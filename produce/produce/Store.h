#pragma once
#include "Player.h"

enum SELECT_ITEM
{
	EMPTY,
	PRODUCT,
};

class Store
{
private:
	int productPrice;
	Player* customer;
	bool isOpen;
	enum SELECT_ITEM sellItem;
public:
	Store();
	~Store();

	void visit(Player* player);

	void update();
	void render();
	void sell(int item);

	void out();

	bool isOpened();
};

