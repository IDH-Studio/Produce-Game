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
							while (true)
							{
								clearBuffer();
								writeBuffer(1, 32, "해당 공장은 이미 열려있습니다.");
								writeBuffer(1, 33, "다른 공장 번호를 선택해주세요.");
								flippingBuffer();
								if (_kbhit())
								{
									*select = MENU;
									break;
								}
							}
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
					while (true)
					{
						writeBuffer(1, 32, "1 ~ 6사이의 번호를 입력해주세요.");
						if (_kbhit())
						{
							*select = MENU;
							break;
						}
					}
				}
			}
			break;
		case DESTROY:
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
							while (true)
							{
								changeBuffer(1, 32, 1, 32, "해당 공장은 이미 닫혀있습니다.");
								changeBuffer(1, 32, 1, 33, "다른 공장 번호를 선택해주세요.");
								if (_kbhit())
								{
									*select = MENU;
									break;
								}
							}
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
					while (true)
					{
						changeBuffer(1, 32, 1, 32, "1 ~ 6사이의 번호를 입력해주세요.");
						if (_kbhit())
						{
							*select = MENU;
							break;
						}
					}
				}
			}
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
		writeBuffer(1, 32, "공장 번호를 입력해주세요(1 ~ 6)");
		break;
	case DESTROY:
		writeBuffer(1, 32, "공장 번호를 입력해주세요(1 ~ 6)");
		break;
	}

	flippingBuffer();
}

void Release(Factory* factory)
{
	delete[] factory;

	const char* over = "Game Over";
	gotoxy((SHORT)((screenWidth / 2) - (strlen(over) / 2)), (SHORT)(screenHeight / 2));
	std::cout << over;
	deleteBuffer();
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