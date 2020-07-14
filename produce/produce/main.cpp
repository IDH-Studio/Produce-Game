#include "Factory.h"
#include "setting.h"
#include "Store.h"
#include "FiberFactory.h"
#include <iostream>
#include <conio.h>

void Init(SELECT* select, Factory** factory, Player** player, Store** store, AREA* area, FiberFactory** fiberFactory)
{
	setCursor(false);
	system("mode con: cols=160 Lines=45");
	createBuffer();

	*select = MENU;
	*area = AREA::FACTORY;
	gameRun = true;
	*factory = new Factory[6];
	*fiberFactory = new FiberFactory[6];
	factoryOperate(*factory, 0);
	*player = new Player();
	*store = new Store();
}

void Update(SELECT* select, Factory* factory, Player* player, Store* store, AREA* area, FiberFactory* fiberFactory)
{
	static int number = 1;
	int key = 0;
	for (int i = 0; i < factorySize; i++)
	{
		factory[i].update(player);
		fiberFactory[i].update(player);
	}

	if (store->isOpened())
	{
		store->update();
	}
	else
	{
		if (_kbhit())
		{
			key = _getch();

			if (inputError != INPUT_ERROR::NONE)
			{
				inputError = INPUT_ERROR::NONE;
			}
			else
			{
				if (*area == AREA::FACTORY)
				{
					if (key == ARROW)
					{
						key = _getch();
						if (key == RIGHT_ARROW)
							*area = AREA::FIBER;
					}
					else
					{
						switch (*select)
						{
						case SELECT::MENU:
							if (key == '1')
							{
								*select = BUILD;
							}
							else if (key == '2')
							{
								*select = DESTROY;
							}
							else if (key == '3')
							{
								store->visit(player);
							}
							else if (key == ESCAPE)
							{
								gameRun = false;
							}
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
				else if (*area == AREA::FIBER)
				{
					if (key == ARROW)
					{
						key = _getch();
						if (key == LEFT_ARROW)
							*area = AREA::FACTORY;
						else if (key == RIGHT_ARROW) {}
					}
					else
					{
						switch (*select)
						{
						case SELECT::MENU:
							if (key == '1')
							{
								*select = BUILD;
							}
							else if (key == '2')
							{
								*select = DESTROY;
							}
							else if (key == '3')
							{
								store->visit(player);
							}
							else if (key == ESCAPE)
							{
								gameRun = false;
							}
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
										if (!factoryOperate(fiberFactory, number - 1))
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
										if (!factoryClose(fiberFactory, number - 1))
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
		}
	}
}

void Render(SELECT select, Factory* factory, Player player, Store* store, AREA area, FiberFactory* fiberFactory)
{
	clearBuffer();

	writeBuffer(0, 31, "================================================================================================================================================================");

	if (store->isOpened())
	{
		store->render();
	}
	else
	{
		if (area == AREA::FACTORY)
		{
			for (int i = 0; i < factorySize; i++)
			{
				factory[i].render();
			}

			if (inputError == INPUT_ERROR::NONE)
			{
				switch (select)
				{
				case SELECT::MENU:
					writeBuffer(1, 32, "1. ���� ����");
					writeBuffer(1, 33, "2. ���� �ı�");
					writeBuffer(1, 34, "3. ����");
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
		}
		else if (area == AREA::FIBER)
		{
			for (int i = 0; i < factorySize; i++)
			{
				fiberFactory[i].render();
			}

			if (inputError == INPUT_ERROR::NONE)
			{
				switch (select)
				{
				case SELECT::MENU:
					writeBuffer(1, 32, "1. ���� ���� ����");
					writeBuffer(1, 33, "2. ���� ���� �ı�");
					writeBuffer(1, 34, "3. ����");
					break;
				case SELECT::BUILD:
					writeBuffer(1, 32, "���� ���� ��ȣ�� �Է����ּ���(1 ~ 6)");
					break;
				case SELECT::DESTROY:
					writeBuffer(1, 32, "���� ���� ��ȣ�� �Է����ּ���(1 ~ 6)");
					break;
				}
			}
			else if (inputError == INPUT_ERROR::EXIST)
			{
				switch (select)
				{
				case SELECT::MENU:
					writeBuffer(1, 32, "1. ���� ���� ����");
					writeBuffer(1, 33, "2. ���� ���� �ı�");
					break;
				case SELECT::BUILD:
					writeBuffer(1, 32, "�ش� ���� ������ �̹� �����ֽ��ϴ�.");
					writeBuffer(1, 33, "�ٸ� ���� ���� ��ȣ�� �������ּ���.");
					break;
				case SELECT::DESTROY:
					writeBuffer(1, 32, "�ش� ���� ������ �̹� �����ֽ��ϴ�.");
					writeBuffer(1, 33, "�ٸ� ���� ���� ��ȣ�� �������ּ���.");
					break;
				}
			}
			else if (inputError == INPUT_ERROR::RANGE)
			{
				switch (select)
				{
				case SELECT::MENU:
					writeBuffer(1, 32, "1. ���� ���� ����");
					writeBuffer(1, 33, "2. ���� ���� �ı�");
					break;
				case SELECT::BUILD:
				case SELECT::DESTROY:
					writeBuffer(1, 32, "1 ~ 6������ ��ȣ�� �Է����ּ���.");
					break;
				}
			}
		}
	}

	player.renderInfo();
	flippingBuffer();
}

void Release(Factory* factory, Player* player, Store* store, FiberFactory* fiberFactory)
{
	delete[] factory;
	delete[] fiberFactory;
	delete player;
	delete store;

	const char* over = "Game Over";
	gotoxy((SHORT)((screenWidth / 2) - (strlen(over) / 2)), (SHORT)(screenHeight / 2));
	std::cout << over;
	deleteBuffer();
	getchar();
}


int main(int argc, char* argv[])
{
	Factory* factory = nullptr;
	FiberFactory* fiberFactory = nullptr;
	Player* player = nullptr;
	Store* store = nullptr;

	enum SELECT select;
	enum AREA area;

	Init(&select, &factory, &player, &store, &area, &fiberFactory);

	while (gameRun)
	{
		Update(&select, factory, player, store, &area, fiberFactory);
		Render(select, factory, *player, store, area, fiberFactory);
		Sleep(60);
	}

	Release(factory, player, store, fiberFactory);

	return 0;
}