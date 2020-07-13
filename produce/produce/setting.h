#pragma once
#include <Windows.h>
#include <string>

#define GET_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

#define ENTER 13
#define ESCAPE 27


extern short screenWidth;
extern short screenHeight;

extern HANDLE hBuffer[2];
extern int nScreenIndex;

extern bool gameRun;
extern char factorySize;

enum SELECT
{
	MENU,
	BUILD,
	DESTROY
};


void createBuffer();
void writeBuffer(int x, int y, const char* str);
void writeBuffer(int x, int y, std::string str);
void flippingBuffer();
void clearBuffer();
//void changeBuffer(SHORT originalX, SHORT originalY, SHORT changeX, SHORT changeY, const char* str);
//void changeBuffer(SHORT originalX, SHORT originalY, SHORT changeX, SHORT changeY, std::string str);
void deleteBuffer();

void gotoxy(SHORT x, SHORT y);
void setCursor(bool visible);