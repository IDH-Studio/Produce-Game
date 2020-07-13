#include "Factory.h"
#include "setting.h"
#include <iostream>
#include <conio.h>

void Init(SELECT* select, Factory* factory)
{
	setCursor(false);
	system("mode con: cols=160 Lines=45");
	createBuffer();

	*select = MENU;
	gameRun = true;
	factoryOperate(factory, 0);
}

void Update(SELECT* select, Factory* factory)
{
	static int number = 1;
	int key = 0;
	for (int i = 0; i < factorySize; i++)
		factory[i].update();

	if (_kbhit())
	{
		key = _getch();

		switch (*select)
		{
		case MENU:
			if (key == '1')
				*select = BUILD;
			else if (key == '2')
				*select = DESTROY;
			else if (key == ESCAPE)
				gameRun = false;
			break;
		case BUILD:
			if (key == ENTER)
			{
				if (number + 1 <= 6)
					factoryOperate(factory, number);
				*select = MENU;
			}
			else if (key == ESCAPE)
				*select = MENU;
			break;
		case DESTROY:
			if (key == ENTER)
			{

			}
			else if (key == ESCAPE)
				*select = MENU;
			break;
		}
	}

}

void Render(SELECT select, Factory* factory)
{
	clearBuffer();

	for (int i = 0; i < factorySize; i++)
		factory[i].render();
	writeBuffer(0, 31, "================================================================================================================================================================");

	switch (select)
	{
	case MENU:
		writeBuffer(1, 32, "1. 공장 생성");
		writeBuffer(1, 33, "2. 공장 파기");
		break;
	case BUILD:
		writeBuffer(1, 32, "공장 생성 부분");
		break;
	case DESTROY:
		writeBuffer(1, 32, "공장 파기 부분");
		break;
	}

	flippingBuffer();
}

void Release(Factory* factory)
{
	delete[] factory;
	deleteBuffer();

	const char* over = "Game Over";
	gotoxy((screenWidth / 2) - (strlen(over) / 2), screenHeight / 2);
	std::cout << over;
	getchar();
}


int main(int argc, char* argv[])
{
	Factory* factory = new Factory[6];
	SELECT select;
	Init(&select, factory);

	while (gameRun)
	{
		Update(&select, factory);
		Render(select, factory);
	}

	Release(factory);

	return 0;
}