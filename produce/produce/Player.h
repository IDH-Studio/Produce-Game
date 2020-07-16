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

	int fabric;
	std::string showFabric;
public:
	Player();
	Player(std::string name);
	~Player();

	void renderInfo();

	void addProduct();
	void addProduct(int product);
	void addFiber();
	void addFiber(int fiber);
	void addFabric();
	void addFabric(int fabric);

	int giveMoney(int money);
	void receiveMoney(int money);
	int giveProduct(int amount);
	void receiveProduct(int amount);
	int giveFiber(int amount);
	void receiveFiber(int amount);
	int giveFabric(int amount);
	void receiveFabric(int amount);

	int getMoney();
	int getProduct();
	int getFiber();
	int getFabric();

	void setMoney(int money);
};