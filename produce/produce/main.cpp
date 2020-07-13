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
							//������ ����������(�̹� ����������)
							while (true)
							{
								clearBuffer();
								writeBuffer(1, 32, "�ش� ������ �̹� �����ֽ��ϴ�.");
								writeBuffer(1, 33, "�ٸ� ���� ��ȣ�� �������ּ���.");
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
							//������ ��������
							*select = MENU;
						}
					}
				}
				else
				{
					while (true)
					{
						writeBuffer(1, 32, "1 ~ 6������ ��ȣ�� �Է����ּ���.");
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
							//������ �� �ݾ�����(�̹� ����������)
							while (true)
							{
								changeBuffer(1, 32, 1, 32, "�ش� ������ �̹� �����ֽ��ϴ�.");
								changeBuffer(1, 32, 1, 33, "�ٸ� ���� ��ȣ�� �������ּ���.");
								if (_kbhit())
								{
									*select = MENU;
									break;
								}
							}
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
					while (true)
					{
						changeBuffer(1, 32, 1, 32, "1 ~ 6������ ��ȣ�� �Է����ּ���.");
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
		writeBuffer(1, 32, "1. ���� ����");
		writeBuffer(1, 33, "2. ���� �ı�");
		break;
	case BUILD:
		writeBuffer(1, 32, "���� ��ȣ�� �Է����ּ���(1 ~ 6)");
		break;
	case DESTROY:
		writeBuffer(1, 32, "���� ��ȣ�� �Է����ּ���(1 ~ 6)");
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