#include "Player.h"
#include "setting.h"


Player::Player() : money(0), product(0), name("unknown")
{
	showProduct = "product: ";
	showMoney = "money: ";
}

Player::Player(std::string name) : money(0), product(0), name(name)
{
	showProduct = "product: ";
	showMoney = "money: ";
}


Player::~Player()
{

}

void Player::renderInfo()
{
	writeBuffer(40, 32, name);
	writeBuffer(40, 33, showProduct + std::to_string(product));
	writeBuffer(40, 34, showMoney + std::to_string(money));
}

void Player::addProduct()
{
	++this->product;
}

void Player::addProduct(int product)
{
	this->product += product;
}

int Player::getMoney()
{
	return money;
}

void Player::setMoney(int money)
{
	this->money = money;
}
