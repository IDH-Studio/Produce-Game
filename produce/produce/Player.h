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

	int giveMoney(int money);
	void receiveMoney(int money);
	int giveProduct(int amount);
	void receiveProduct(int amount);
	int giveFiber(int amount);
	void receiveFiber(int amount);

	int getMoney();
	int getProduct();
	int getFiber();

	void setMoney(int money);
};