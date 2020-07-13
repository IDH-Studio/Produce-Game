#pragma once
#include <string>

class Player
{
private:
	std::string name;

	int money;
	std::string showMoney;

	int product;
	std::string showProduct;
public:
	Player();
	Player(std::string name);
	~Player();

	void renderInfo();

	void addProduct();
	void addProduct(int product);

	int getMoney();

	void setMoney(int money);
};