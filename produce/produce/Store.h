#pragma once
#include "Player.h"

namespace store
{
	enum SELECT_ITEM
	{
		EMPTY,
		PRODUCT,
		FIBER,
	};

	struct Price
	{
		int product;
		int fiber;
	};

	struct Quantity
	{
		int product;
		int fiber;
	};
}
using namespace store;

class Store
{
private:
	struct Quantity quantity;
	struct Price price;
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

