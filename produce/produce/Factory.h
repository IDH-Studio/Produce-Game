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
	int money;
	int factoryNumber;
	bool isOperate;
	clock_t start, end;
	FACTORY_RECT fRect;
	std::string showMoney, showNumber;
public:
	Factory();
	Factory(int number);
	~Factory();

	void operate(int number);
	void update();
	void render();
};


void drawRect(MY_RECT rect);
void factoryOperate(Factory* factory, int number);