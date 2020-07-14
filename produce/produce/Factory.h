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
}FACTORY_RECT, MY_RECT;

class Factory
{
private:
	int product;
	bool isOperate;
	int factoryNumber;
	clock_t start, end;
	FACTORY_RECT fRect;
	std::string showProduct, showNumber;
protected:
	void setShowProduct(std::string productName);
	void addProduct();
	clock_t getStart();
	clock_t getEnd();
	void setStart();
	void setEnd();
public:
	Factory();
	Factory(int number);
	~Factory();

	void operate(int number);
	void close(int number);
	void update(Player* player);
	void render();
	bool isOperated();

	// getter
	int getProduct();
	int getFactoryNumber();
};


bool factoryOperate(Factory* factory, int number);
bool factoryClose(Factory* factory, int number);