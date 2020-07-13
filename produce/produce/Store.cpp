#include "Store.h"



Store::Store() : customer(nullptr), productPrice(2), isOpen(false)
{
}


Store::~Store()
{
	customer = nullptr;
}

void Store::visit(Player* player)
{
	customer = player;
	isOpen = true;
}

void Store::sell()
{

}

void Store::out()
{
	customer = nullptr;
	isOpen = false;
}
