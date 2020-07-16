#include "Player.h"
#include "setting.h"


Player::Player() : money(objectCost.factoryCost), product(0), name("unknown"), fiber(0), fabric(0)
{
	showProduct = "product: ";
	showMoney = "money: ";
	showFiber = "fiber: ";
	showFabric = "fabric: ";
}

Player::Player(std::string name) : money(objectCost.factoryCost), product(0), name(name), fiber(0), fabric(0)
{
	showProduct = "product: ";
	showMoney = "money: ";
	showFiber = "fiber: ";
	showFabric = "fabric: ";
}


Player::~Player()
{

}

void Player::renderInfo()
{
	setColor(WHITE);
	writeBuffer(screenWidth - 16, 32, name);
	writeBuffer(screenWidth - 16, 33, showProduct + std::to_string(product));
	writeBuffer(screenWidth - 16, 34, showFiber + std::to_string(fiber));
	writeBuffer(screenWidth - 16, 35, showFabric + std::to_string(fabric));
	writeBuffer(screenWidth - 16, 36, showMoney + std::to_string(money));
}

void Player::addProduct()
{
	++this->product;
}

void Player::addProduct(int product)
{
	this->product += product;
}

void Player::addFiber()
{
	++this->fiber;
}

void Player::addFiber(int fiber)
{
	this->fiber += fiber;
}

void Player::addFabric()
{
	++this->fabric;
}

void Player::addFabric(int fabric)
{
	this->fiber += fabric;
}

int Player::getMoney()
{
	return money;
}

int Player::giveMoney(int money)
{
	if (money < 0)
	{
		this->money += money;
		return -money;
	}
	else
	{
		this->money -= money;
		return money;
	}
}

void Player::receiveMoney(int money)
{
	if (money < 0)
	{
		this->money -= money;
	}
	else
	{
		this->money += money;
	}
}

int Player::giveProduct(int amount)
{
	if (amount < 0)
	{
		this->product += amount;
		return amount;
	}
	else
	{
		this->product -= amount;
		return amount;
	}
}

void Player::receiveProduct(int amount)
{
	if (amount < 0)
	{
		this->product -= amount;
	}
	else
	{
		this->product += amount;
	}
}

int Player::giveFiber(int amount)
{
	if (amount < 0)
	{
		this->fiber += amount;
		return amount;
	}
	else
	{
		this->fiber -= amount;
		return amount;
	}
}

void Player::receiveFiber(int amount)
{
	if (amount < 0)
	{
		this->fiber -= amount;
	}
	else
	{
		this->fiber += amount;
	}
}

int Player::giveFabric(int amount)
{
	if (amount < 0)
	{
		this->fabric += amount;
		return amount;
	}
	else
	{
		this->fabric -= amount;
		return amount;
	}
}

void Player::receiveFabric(int amount)
{
	if (amount < 0)
	{
		this->fabric -= amount;
	}
	else
	{
		this->fabric += amount;
	}
}

int Player::getProduct()
{
	return product;
}

int Player::getFiber()
{
	return fiber;
}

int Player::getFabric()
{
	return fabric;
}

void Player::setMoney(int money)
{
	this->money = money;
}
