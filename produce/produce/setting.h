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

#define PAUSE_RESUME 0b00000001
#define PAUSE_EXIT 0b00000010

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
		MONEY,
	};

	struct ErrorMessage
	{
		std::string activateError;
		std::string deactivateError;
		std::string buyError;
		std::string rangeError;
	};

	struct COST
	{
		unsigned short factoryCost;
		unsigned short fiberCost;
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

extern bool gameRun;
extern bool isPause;
extern char pauseState;
extern struct PauseArrow pauseArrow;

extern enum INPUT_ERROR inputError;
extern struct ErrorMessage errorMessage;

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