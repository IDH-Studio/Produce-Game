#include "Game.h"


Game::Game()
{
	setCursor(false);
	system("mode con: cols=160 Lines=45");
	createBuffer();

	select = SELECT::MENU;
	area = AREA::FACTORY;
	gameRun = true;
	isPause = false;
	
	objectCost.factoryCost = 80;
	objectCost.fiberCost = 100;
	objectCost.fabricCost.money = 100;
	objectCost.fabricCost.fiber = 10;

	pauseArrow.x = screenWidth / 2 - 7;
	pauseArrow.y = screenHeight / 2 - 1;
	pauseArrow.arrow = '>';

	for (int i = 0; i < objectSize; i++)
	{
		factory[i] = Factory(i);
		fiberFarm[i] = FiberFarm(i);
		fabricFactory[i] = FabricFactory(i);
	}

	player = new Player();
	store = new Store();

	factory[0].canBuy(player, 0);
}


Game::~Game()
{
	delete player;
	delete store;

	deleteBuffer();
}

void Game::update()
{
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
					if (area == AREA::FACTORY)
					{
						// 공장
						if (key == ARROW)
						{
							key = _getch();
							if (key == RIGHT_ARROW)
							{
								area = AREA::FIBER;
								select = MENU;
							}
						}
						else
						{
							switch (select)
							{
							case SELECT::MENU:
								if (key == '1')
									select = BUILD;
								else if (key == '2')
									select = DESTROY;
								else if (key == '3')
									store->visit(player);
								else if (key == ESCAPE)
									isPause = true;
								break;
							case SELECT::BUILD:
								if (key == ESCAPE)
									select = MENU;
								else
								{
									if ('1' <= key && key <= '6')
									{
										number = key % '0';

										if (1 <= number && number <= 6)
										{
											char tryBuy = factory[number - 1].canBuy(player);
											if (tryBuy & CAN_OPEN)
											{
												//공장을 샀으면
												select = MENU;
											}
											else if (tryBuy & CANT_OPEN)
											{
												//이미 열려있으면
												inputError = INPUT_ERROR::EXIST;
											}
											else if (tryBuy & CANT_BUY)
											{
												//돈이 부족하면
												inputError = INPUT_ERROR::BUY;
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
									select = MENU;
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
												select = MENU;
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
					else if (area == AREA::FIBER)
					{
						// 섬유 농장
						if (key == ARROW)
						{
							key = _getch();
							if (key == LEFT_ARROW)
							{
								area = AREA::FACTORY;
								select = MENU;
							}
							else if (key == RIGHT_ARROW)
							{
								// 다른 지역이 생겼을 때 추가
								area = AREA::FABRIC;
								select = MENU;
							}
						}
						else
						{
							switch (select)
							{
							case SELECT::MENU:
								if (key == '1')
									select = BUILD;
								else if (key == '2')
									select = DESTROY;
								else if (key == '3')
									store->visit(player);
								else if (key == ESCAPE)
									isPause = true;
								break;
							case SELECT::BUILD:
								if (key == ESCAPE)
									select = MENU;
								else
								{
									if ('1' <= key && key <= '6')
									{
										number = key % '0';

										if (1 <= number && number <= 6)
										{
											char tryBuy = fiberFarm[number - 1].canBuy(player);
											if (tryBuy & CAN_OPEN)
											{
												//섬유 농장을 샀으면
												select = MENU;
											}
											else if (tryBuy & CANT_OPEN)
											{
												//섬유 농장을 못샀으면(이미 샀으면)
												inputError = INPUT_ERROR::EXIST;
											}
											else if (tryBuy & CANT_BUY)
											{
												inputError = INPUT_ERROR::BUY;
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
									select = MENU;
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
												select = MENU;
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
					else if (area == AREA::FABRIC)
					{
						// 섬유 농장
						if (key == ARROW)
						{
							key = _getch();
							if (key == LEFT_ARROW)
							{
								area = AREA::FIBER;
								select = MENU;
							}
							else if (key == RIGHT_ARROW)
							{
								// 다른 지역이 생겼을 때 추가
								/**area = AREA::
								*select = MENU;*/
							}
						}
						else
						{
							switch (select)
							{
							case SELECT::MENU:
								if (key == '1')
									select = BUILD;
								else if (key == '2')
									select = DESTROY;
								else if (key == '3')
									store->visit(player);
								else if (key == ESCAPE)
									isPause = true;
								break;
							case SELECT::BUILD:
								if (key == ESCAPE)
									select = MENU;
								else
								{
									if ('1' <= key && key <= '6')
									{
										number = key % '0';

										if (1 <= number && number <= 6)
										{
											char tryBuy = fabricFactory[number - 1].canBuy(player);
											if (tryBuy & CAN_OPEN)
											{
												//섬유 농장을 샀으면
												select = MENU;
											}
											else if (tryBuy & CANT_OPEN)
											{
												//섬유 농장을 못샀으면(이미 샀으면)
												inputError = INPUT_ERROR::EXIST;
											}
											else if (tryBuy & CANT_BUY)
											{
												inputError = INPUT_ERROR::BUY;
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
									select = MENU;
								else
								{
									if ('1' <= key && key <= '6')
									{
										number = key % '0';

										if (1 <= number && number <= 6)
										{
											if (fabricFactory[number - 1].close())
											{
												//섬유 농장을 닫았으면
												select = MENU;
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
		if (_kbhit())
		{
			key = _getch();
			if (key == ARROW)
			{
				key = _getch();
				if (key == UP_ARROW && !(pauseState & PAUSE_RESUME))
				{
					pauseArrow.y -= 2;
					pauseState >>= 1;
				}
				else if (key == DOWN_ARROW && !(pauseState & PAUSE_EXIT))
				{
					pauseArrow.y += 2;
					pauseState <<= 1;
				}
			}
			else
			{
				if (key == ESCAPE)
					isPause = false;
				else if (key == ENTER)
				{
					if (pauseState & PAUSE_RESUME)
					{
						isPause = false;
					}
					else if (pauseState & PAUSE_EXIT)
					{
						gameRun = false;
					}
				}
			}
		}
	}
}

void Game::render()
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
						setColor(WHITE);
						writeBuffer(1, 32, "1. 공장 생성");
						writeBuffer(1, 33, "2. 공장 파기");
						writeBuffer(1, 34, "3. 상점");
						break;
					case SELECT::BUILD:
						setColor(WHITE);
						writeBuffer(1, 32, "공장 번호를 입력해주세요(1 ~ 6)");
						break;
					case SELECT::DESTROY:
						setColor(WHITE);
						writeBuffer(1, 32, "공장 번호를 입력해주세요(1 ~ 6)");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::EXIST)
				{
					switch (select)
					{
					case SELECT::BUILD:
						factory[number - 1].showError(1, 32, "active");
						break;
					case SELECT::DESTROY:
						factory[number - 1].showError(1, 32, "deactive");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::RANGE)
				{
					switch (select)
					{
					case SELECT::BUILD:
					case SELECT::DESTROY:
						factory[number - 1].showError(1, 32, "range");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::BUY)
				{
					factory[number - 1].showError(1, 32, "buy");
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
						setColor(WHITE);
						writeBuffer(1, 32, "1. 섬유 농장 생성");
						writeBuffer(1, 33, "2. 섬유 농장 파기");
						writeBuffer(1, 34, "3. 상점");
						break;
					case SELECT::BUILD:
						setColor(WHITE);
						writeBuffer(1, 32, "섬유 농장 번호를 입력해주세요(1 ~ 6)");
						break;
					case SELECT::DESTROY:
						setColor(WHITE);
						writeBuffer(1, 32, "섬유 농장 번호를 입력해주세요(1 ~ 6)");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::EXIST)
				{
					switch (select)
					{
					case SELECT::BUILD:
						fiberFarm[number - 1].showError(1, 32, "active");
						break;
					case SELECT::DESTROY:
						fiberFarm[number - 1].showError(1, 32, "deactive");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::RANGE)
				{
					switch (select)
					{
					case SELECT::BUILD:
					case SELECT::DESTROY:
						fiberFarm[number - 1].showError(1, 32, "range");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::BUY)
				{
					fiberFarm[number - 1].showError(1, 32, "buy");
				}
			}
			else if (area == AREA::FABRIC)
			{
				writeBuffer(1, 43, "섬유 공장");
				for (int i = 0; i < objectSize; i++)
				{
					fabricFactory[i].render();
				}

				if (inputError == INPUT_ERROR::NONE)
				{
					switch (select)
					{
					case SELECT::MENU:
						setColor(WHITE);
						writeBuffer(1, 32, "1. 섬유 공장 생성");
						writeBuffer(1, 33, "2. 섬유 공장 파기");
						writeBuffer(1, 34, "3. 상점");
						break;
					case SELECT::BUILD:
						setColor(WHITE);
						writeBuffer(1, 32, "섬유 공장 번호를 입력해주세요(1 ~ 6)");
						break;
					case SELECT::DESTROY:
						setColor(WHITE);
						writeBuffer(1, 32, "섬유 농장 번호를 입력해주세요(1 ~ 6)");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::EXIST)
				{
					switch (select)
					{
					case SELECT::BUILD:
						fabricFactory[number - 1].showError(1, 32, "active");
						break;
					case SELECT::DESTROY:
						fabricFactory[number - 1].showError(1, 32, "deactive");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::RANGE)
				{
					switch (select)
					{
					case SELECT::BUILD:
					case SELECT::DESTROY:
						fabricFactory[number - 1].showError(1, 32, "range");
						break;
					}
				}
				else if (inputError == INPUT_ERROR::BUY)
				{
					fabricFactory[number - 1].showError(1, 32, "buy");
				}
			}
		}

		player->renderInfo();
	}
	else
	{
		// ESC를 눌렀을 때
		// 게임으로 돌아가기
		// 게임 종료
		writeBuffer(screenWidth / 2 - 5, screenHeight / 2 - 1, "게임으로 돌아가기");
		writeBuffer(screenWidth / 2 - 2, screenHeight / 2 + 1, "게임 종료");
		writeBuffer(pauseArrow.x, pauseArrow.y, pauseArrow.arrow);
	}
	flippingBuffer();
}

void Game::run()
{
	while (gameRun)
	{
		update();
		render();
		Sleep(33);
	}
}