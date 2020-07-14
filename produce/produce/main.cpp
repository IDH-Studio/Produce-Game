#include "Factory.h"
#include "setting.h"
#include "Store.h"
#include "FiberFarm.h"
#include <iostream>
#include <conio.h>

/*
	TODO
	일시정지 메뉴
	공장, 농장 등을 생성할 때 가격이 있음 -> 완료
	올바른 에러 메세지 출력
*/

void Init(SELECT* select, Factory factory[], Player** player, Store** store, AREA* area, FiberFarm fiberFarm[])
{
	setCursor(false);
	system("mode con: cols=160 Lines=45");
	createBuffer();

	*select = MENU;
	*area = AREA::FACTORY;
	gameRun = true;
	isPause = false;
	for (int i = 0; i < objectSize; i++)
	{
		factory[i] = Factory(i);
		fiberFarm[i] = FiberFarm(i);
	}
	*player = new Player();
	*store = new Store();
	factory[0].canBuy(*player, 0);
}

void Update(SELECT* select, Factory* factory, Player* player, Store* store, AREA* area, FiberFarm* fiberFarm)
{
	static int number = 1;
	int key = 0;

	if (!isPause)
	{
		for (int i = 0; i < objectSize; i++)
		{
			factory[i].update(player);
			fiberFarm[i].update(player);
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
						// 공장
						if (key == ARROW)
						{
							key = _getch();
							if (key == RIGHT_ARROW)
							{
								*area = AREA::FIBER;
								*select = MENU;
							}
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
								else if (key == '3')
									store->visit(player);
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
											if (factory[number - 1].canBuy(player, number - 1))
											{
												//공장을 샀으면
												*select = MENU;
											}
											else
											{
												//공장을 못샀으면(이미 샀으면)
												inputError = INPUT_ERROR::EXIST;
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
											if (factory[number - 1].close())
											{
												//공장을 닫았으면
												*select = MENU;
											}
											else
											{
												//공장을 못 닫았으면(이미 닫혀있으면)
												inputError = INPUT_ERROR::EXIST;
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
						// 섬유 농장
						if (key == ARROW)
						{
							key = _getch();
							if (key == LEFT_ARROW)
							{
								*area = AREA::FACTORY;
								*select = MENU;
							}
							else if (key == RIGHT_ARROW)
							{
								// 다른 지역이 생겼을 때 추가
							}
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
								else if (key == '3')
									store->visit(player);
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
											if (fiberFarm[number - 1].canBuy(player, number - 1))
											{
												//섬유 농장을 샀으면
												*select = MENU;
											}
											else
											{
												//섬유 농장을 못샀으면(이미 샀으면)
												inputError = INPUT_ERROR::EXIST;
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
											if (fiberFarm[number - 1].close())
											{
												//섬유 농장을 닫았으면
												*select = MENU;
											}
											else
											{
												//섬유 농장을 못 닫았으면(이미 닫혀있으면)
												inputError = INPUT_ERROR::EXIST;
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
	else
	{
		// ESC를 눌렀을 때
		
	}
}

void Render(SELECT select, Factory* factory, Player player, Store* store, AREA area, FiberFarm* fiberFarm)
{
	clearBuffer();
	if (!isPause)
	{
		writeBuffer(0, 31, "================================================================================================================================================================");

		if (store->isOpened())
		{
			store->render();
		}
		else
		{
			if (area == AREA::FACTORY)
			{
				writeBuffer(1, 43, "공장");
				for (int i = 0; i < objectSize; i++)
				{
					factory[i].render();
				}

				if (inputError == INPUT_ERROR::NONE)
				{
					switch (select)
					{
					case SELECT::MENU:
						writeBuffer(1, 32, "1. 공장 생성");
						writeBuffer(1, 33, "2. 공장 파기");
						writeBuffer(1, 34, "3. 상점");
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
			}
			else if (area == AREA::FIBER)
			{
				writeBuffer(1, 43, "섬유 농장");
				for (int i = 0; i < objectSize; i++)
				{
					fiberFarm[i].render();
				}

				if (inputError == INPUT_ERROR::NONE)
				{
					switch (select)
					{
					case SELECT::MENU:
						writeBuffer(1, 32, "1. 섬유 농장 생성");
						writeBuffer(1, 33, "2. 섬유 농장 파기");
						writeBuffer(1, 34, "3. 상점");
						break;
					case SELECT::BUILD:
						writeBuffer(1, 32, "섬유 농장 번호를 입력해주세요(1 ~ 6)");
						break;
					case SELECT::DESTROY:
						writeBuffer(1, 32, "섬유 농장 번호를 입력해주세요(1 ~ 6)");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::EXIST)
				{
					switch (select)
					{
					case SELECT::MENU:
						writeBuffer(1, 32, "1. 섬유 농장 생성");
						writeBuffer(1, 33, "2. 섬유 농장 파기");
						break;
					case SELECT::BUILD:
						writeBuffer(1, 32, "해당 섬유 농장은 이미 열려있습니다.");
						writeBuffer(1, 33, "다른 섬유 농장 번호를 선택해주세요.");
						break;
					case SELECT::DESTROY:
						writeBuffer(1, 32, "해당 섬유 농장은 이미 닫혀있습니다.");
						writeBuffer(1, 33, "다른 섬유 농장 번호를 선택해주세요.");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::RANGE)
				{
					switch (select)
					{
					case SELECT::MENU:
						writeBuffer(1, 32, "1. 섬유 농장 생성");
						writeBuffer(1, 33, "2. 섬유 농장 파기");
						break;
					case SELECT::BUILD:
					case SELECT::DESTROY:
						writeBuffer(1, 32, "1 ~ 6사이의 번호를 입력해주세요.");
						break;
					}
				}
			}
		}

		player.renderInfo();
	}
	else
	{
		// ESC를 눌렀을 때
	}
	flippingBuffer();
}

void Release(Player* player, Store* store)
{
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
	Factory factory[6];
	FiberFarm fiberFarm[6];
	Player* player = nullptr;
	Store* store = nullptr;

	enum SELECT select;
	enum AREA area;

	Init(&select, factory, &player, &store, &area, fiberFarm);

	while (gameRun)
	{
		Update(&select, factory, player, store, &area, fiberFarm);
		Render(select, factory, *player, store, area, fiberFarm);
		Sleep(33);
	}

	Release(player, store);

	return 0;
}