#pragma once
#include <time.h>
#include <string>

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
	int factoryNumber;
	bool isOperate;
	clock_t start, end;
	FACTORY_RECT fRect;
	std::string showProduct, showNumber;
public:
	Factory();
	Factory(int number);
	~Factory();

	void operate(int number);
	void close(int number);
	void update();
	void render();
	bool isOperated();

	// getter
	int getProduct();
	int getFactoryNumber();
};


void drawRect(MY_RECT rect);
bool factoryOperate(Factory* factory, int number);
bool factoryClose(Factory* factory, int number);