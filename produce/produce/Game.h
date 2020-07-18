#pragma once
#include "setting.h"
#include "Factory.h"
#include "FabricFactory.h"
#include "FiberFarm.h"
#include "ClothFactory.h"
#include "Store.h"
#include <iostream>
#include <conio.h>


class Game
{
private:
	Factory factory[6];
	FiberFarm fiberFarm[6];
	FabricFactory fabricFactory[6];
	ClothFactory clothFactory[6];
	Player* player;
	Store* store;

	enum SELECT select;
	enum AREA area;
	struct PauseArrow pauseArrow;

	bool gameRun;
	bool isPause;
	char pauseState;
	char number;
public:
	Game();
	~Game();

	void update();
	void render();
	void run();
};

