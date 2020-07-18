#pragma once
#include <Windows.h>
#include <string>

#define GET_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

#define BACKSPACE 8
#define ENTER 13
#define ESCAPE 27

#define ARROW 224
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

#define PAUSE_RESUME 0b00000001
#define PAUSE_EXIT 0b00000010

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define LIGHT_GREY 15

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
		FABRIC,
		CLOTH,
	};

	enum INPUT_ERROR
	{
		NONE,
		EXIST,
		RANGE,
		BUY,
	};

	struct ErrorMessage
	{
		std::string activateError;
		std::string deactivateError;
		std::string buyError;
		std::string rangeError;
	};

	struct FabricCost
	{
		unsigned short money;
		unsigned short fiber;
	};

	struct ClothCost
	{
		unsigned short money;
		unsigned short fabric;
	};

	struct COST
	{
		unsigned short factoryCost;
		unsigned short fiberCost;
		struct FabricCost fabricCost;
		struct ClothCost clothCost;
	};

	struct PauseArrow
	{
		int x;
		int y;
		std::string arrow;
	};
};
using namespace setting;

extern short screenWidth;
extern short screenHeight;

extern HANDLE hBuffer[2];
extern int nScreenIndex;

extern enum INPUT_ERROR inputError;

extern struct COST objectCost;
extern char objectSize;


void createBuffer();
void writeBuffer(SHORT x, SHORT y, const char* str);
void writeBuffer(SHORT x, SHORT y, std::string str);
void flippingBuffer();
void clearBuffer();
void deleteBuffer();

void gotoxy(SHORT x, SHORT y);
void setCursor(bool visible);
void setColor(int textColor, int backgroundColor=BLACK);