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
								//������ ����������(�̹� ����������)
								inputError = INPUT_ERROR::EXIST;
							}
							else
							{
								//������ ��������
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
								//������ �� �ݾ�����(�̹� ����������)
								inputError = INPUT_ERROR::EXIST;
							}
							else
							{
								//������ �������
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
			writeBuffer(1, 32, "1. ���� ����");
			writeBuffer(1, 33, "2. ���� �ı�");
			break;
		case SELECT::BUILD:
			writeBuffer(1, 32, "���� ��ȣ�� �Է����ּ���(1 ~ 6)");
			break;
		case SELECT::DESTROY:
			writeBuffer(1, 32, "���� ��ȣ�� �Է����ּ���(1 ~ 6)");
			break;
		}
	}
	else if (inputError == INPUT_ERROR::EXIST)
	{
		switch (select)
		{
		case SELECT::MENU:
			writeBuffer(1, 32, "1. ���� ����");
			writeBuffer(1, 33, "2. ���� �ı�");
			break;
		case SELECT::BUILD:
			writeBuffer(1, 32, "�ش� ������ �̹� �����ֽ��ϴ�.");
			writeBuffer(1, 33, "�ٸ� ���� ��ȣ�� �������ּ���.");
			break;
		case SELECT::DESTROY:
			writeBuffer(1, 32, "�ش� ������ �̹� �����ֽ��ϴ�.");
			writeBuffer(1, 33, "�ٸ� ���� ��ȣ�� �������ּ���.");
			break;
		}
	}
	else if (inputError == INPUT_ERROR::RANGE)
	{
		switch (select)
		{
		case SELECT::MENU:
			writeBuffer(1, 32, "1. ���� ����");
			writeBuffer(1, 33, "2. ���� �ı�");
			break;
		case SELECT::BUILD:
		case SELECT::DESTROY:
			writeBuffer(1, 32, "1 ~ 6������ ��ȣ�� �Է����ּ���.");
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