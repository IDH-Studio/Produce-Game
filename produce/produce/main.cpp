#include "Factory.h"
#include "setting.h"
#include <iostream>
#include <conio.h>

void Init(SELECT* select, Factory** factory, Player** player)
{
	setCursor(false);
	system("mode con: cols=160 Lines=45");
	createBuffer();

	*select = MENU;
	gameRun = true;
	*factory = new Factory[6];
	factoryOperate(*factory, 0);
	*player = new Player();
}

void Update(SELECT* select, Factory* factory, Player* player)
{
	static int number = 1;
	int key = 0;
	for (int i = 0; i < factorySize; i++)
		factory[i].update(player);

	if (_kbhit())
	{
		key = _getch();

		if (inputError != INPUT_ERROR::NONE)
		{
			inputError = INPUT_ERROR::NONE;
		}
		else
		{
			switch (*select)
			{
			case SELECT::MENU:
				if (key == '1')
					*select = BUILD;
				else if (key == '2')
					*select = DESTROY;
				else if (key == ESCAPE)
					gameRun = false;
				break;
			case SELECT::BUILD:
				if (key == ESCAPE)
					*select = MENU;
				else
				{
					if ('1' <= key && key <= '6')
					{
						number = key % '0';

						if (1 <= number && number <= 6)
						{
							if (!factoryOperate(factory, number - 1))
							{
								//공장을 못열었으면(이미 열려있으면)
								inputError = INPUT_ERROR::EXIST;
							}
							else
							{
								//공장을 열었으면
								*select = MENU;
							}
						}
					}
					else
					{
						inputError = INPUT_ERROR::RANGE;
					}
				}
				break;
			case SELECT::DESTROY:
				if (key == ESCAPE)
					*select = MENU;
				else
				{
					if ('1' <= key && key <= '6')
					{
						number = key % '0';

						if (1 <= number && number <= 6)
						{
							if (!factoryClose(factory, number - 1))
							{
								//공장을 못 닫았으면(이미 닫혀있으면)
								inputError = INPUT_ERROR::EXIST;
							}
							else
							{
								//공장을 닸았으면
								*select = MENU;
							}
						}
					}
					else
					{
						inputError = INPUT_ERROR::RANGE;
					}
				}
				break;
			}
		}
	}

}

void Render(SELECT select, Factory* factory, Player player)
{
	clearBuffer();

	for (int i = 0; i < factorySize; i++)
		factory[i].render();
	writeBuffer(0, 31, "================================================================================================================================================================");

	if (inputError == INPUT_ERROR::NONE)
	{
		switch (select)
		{
		case SELECT::MENU:
			writeBuffer(1, 32, "1. 공장 생성");
			writeBuffer(1, 33, "2. 공장 파기");
			break;
		case SELECT::BUILD:
			writeBuffer(1, 32, "공장 번호를 입력해주세요(1 ~ 6)");
			break;
		case SELECT::DESTROY:
			writeBuffer(1, 32, "공장 번호를 입력해주세요(1 ~ 6)");
			break;
		}
	}
	else if (inputError == INPUT_ERROR::EXIST)
	{
		switch (select)
		{
		case SELECT::MENU:
			writeBuffer(1, 32, "1. 공장 생성");
			writeBuffer(1, 33, "2. 공장 파기");
			break;
		case SELECT::BUILD:
			writeBuffer(1, 32, "해당 공장은 이미 열려있습니다.");
			writeBuffer(1, 33, "다른 공장 번호를 선택해주세요.");
			break;
		case SELECT::DESTROY:
			writeBuffer(1, 32, "해당 공장은 이미 닫혀있습니다.");
			writeBuffer(1, 33, "다른 공장 번호를 선택해주세요.");
			break;
		}
	}
	else if (inputError == INPUT_ERROR::RANGE)
	{
		switch (select)
		{
		case SELECT::MENU:
			writeBuffer(1, 32, "1. 공장 생성");
			writeBuffer(1, 33, "2. 공장 파기");
			break;
		case SELECT::BUILD:
		case SELECT::DESTROY:
			writeBuffer(1, 32, "1 ~ 6사이의 번호를 입력해주세요.");
			break;
		}
	}

	player.renderInfo();
	flippingBuffer();
}

void Release(Factory* factory, Player* player)
{
	delete[] factory;
	delete player;

	const char* over = "Game Over";
	gotoxy((SHORT)((screenWidth / 2) - (strlen(over) / 2)), (SHORT)(screenHeight / 2));
	std::cout << over;
	deleteBuffer();
	getchar();
}


int main(int argc, char* argv[])
{
	Factory* factory = nullptr;
	enum SELECT select;
	Player* player = nullptr;
	Init(&select, &factory, &player);

	while (gameRun)
	{
		Update(&select, factory, player);
		Render(select, factory, *player);
	}

	Release(factory, player);

	return 0;
}