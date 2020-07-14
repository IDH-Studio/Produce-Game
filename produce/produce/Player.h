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

	int fiber;
	std::string showFiber;
public:
	Player();
	Player(std::string name);
	~Player();

	void renderInfo();

	void addProduct();
	void addProduct(int product);
	void addFiber();
	void addFiber(int fiber);
	void addMoney();
	void addMoney(int money);

	int getMoney();
	int getProduct();

	void setMoney(int money);
	void setProduct(int amount);
};