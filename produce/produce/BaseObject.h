#pragma once
#include <time.h>
#include <string>
#include "Player.h"

typedef struct
{
	int x;
	int y;
	int w;
	int h;
}OBJECT_RECT;

class BaseObject
{
private:
	int product;
	int objectNumber;
	bool isActivate;
	clock_t curTime, lastTime;
	OBJECT_RECT rect;
	std::string showProduct, showNumber;
protected:
	void setShowProduct(std::string productName);
	void setWhatNumber(std::string whatNumber);
	void addProduct();
	clock_t getCurTime();
	void setCurTime();
	clock_t getLastTime();
	void setLastTime();
	OBJECT_RECT getRect();
	std::string getShowNumber();
	std::string getShowProduct();
public:
	BaseObject();
	BaseObject(int number);
	~BaseObject();

	void active(int number);
	bool close();
	void update(Player* player);
	void render();
	bool canBuy(Player* player, int number);

	// getter
	bool checkActivate();
	int getProduct();
	int getNumber();
};