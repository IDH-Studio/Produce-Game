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

	int cloth;
	std::string showCloth;
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
	void addCloth();
	void addCloth(int cloth);

	int giveMoney(int money);
	void receiveMoney(int money);
	int giveProduct(int amount);
	void receiveProduct(int amount);
	int giveFiber(int amount);
	void receiveFiber(int amount);
	int giveFabric(int amount);
	void receiveFabric(int amount);
	int giveCloth(int amount);
	void receiveCloth(int amount);

	int getMoney();
	int getProduct();
	int getFiber();
	int getFabric();
	int getCloth();

	void setMoney(int money);
};