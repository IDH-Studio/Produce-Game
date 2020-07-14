#include "Player.h"
#include "setting.h"


Player::Player() : money(0), product(0), name("unknown"), fiber(0)
{
	showProduct = "product: ";
	showMoney = "money: ";
	showFiber = "fiber: ";
}

Player::Player(std::string name) : money(0), product(0), name(name), fiber(0)
{
	showProduct = "product: ";
	showMoney = "money: ";
	showFiber = "fiber: ";
}


Player::~Player()
{

}

void Player::renderInfo()
{
	writeBuffer(screenWidth - 16, 32, name);
	writeBuffer(screenWidth - 16, 33, showProduct + std::to_string(product));
	writeBuffer(screenWidth - 16, 34, showFiber + std::to_string(fiber));
	writeBuffer(screenWidth - 16, 35, showMoney + std::to_string(money));
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


void Player::addMoney()
{
	++this->money;
}

void Player::addMoney(int money)
{
	this->money += money;
}

void Player::setProduct(int amount)
{
	if (amount < 0)
	{
		this->product += amount;
	}
	else
	{
		this->product -= amount;
	}
}

int Player::getMoney()
{
	return money;
}

int Player::getProduct()
{
	return product;
}

void Player::setMoney(int money)
{
	this->money = money;
}
