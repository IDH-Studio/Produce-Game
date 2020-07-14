#pragma once
#include <Windows.h>
#include <string>

#define GET_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

#define ENTER 13
#define ESCAPE 27

#define ARROW 224
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

namespace setting
{
	enum SELECT
	{
		MENU,
		BUILD,
		DESTROY,
	};

	enum AREA
	{
		FACTORY,
		FIBER,
	};

	enum INPUT_ERROR
	{
		NONE,
		EXIST,
		RANGE,
	};

	struct COST
	{
		unsigned short factoryCost;
		unsigned short fiberCost;
	};
};
using namespace setting;

extern short screenWidth;
extern short screenHeight;

extern HANDLE hBuffer[2];
extern int nScreenIndex;

extern bool gameRun;
extern bool isPause;
extern enum INPUT_ERROR inputError;
extern struct COST objectCost;
extern char objectSize;

void createBuffer();
void writeBuffer(int x, int y, const char* str);
void writeBuffer(int x, int y, std::string str);
void flippingBuffer();
void clearBuffer();
void deleteBuffer();

void gotoxy(SHORT x, SHORT y);
void setCursor(bool visible);