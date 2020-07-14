#include "setting.h"

short screenWidth = 160;
short screenHeight = 45;

HANDLE hBuffer[2];
int nScreenIndex;

bool gameRun;
bool isPause;
enum INPUT_ERROR inputError = NONE;
struct COST objectCost = { 80, 100 };
char objectSize = 6;


void createBuffer()
{
	COORD size = { screenWidth, screenHeight };
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = screenWidth - 1;
	rect.Top = 0;
	rect.Bottom = screenHeight - 1;

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);
}

void writeBuffer(int x, int y, const char* str)
{
	DWORD dw;
	COORD pos = { x, y };

	SetConsoleCursorPosition(hBuffer[nScreenIndex], pos);
	WriteFile(hBuffer[nScreenIndex], str, strlen(str), &dw, NULL);
}

void writeBuffer(int x, int y, std::string str)
{
	DWORD dw;
	COORD pos = { x, y };

	SetConsoleCursorPosition(hBuffer[nScreenIndex], pos);
	WriteFile(hBuffer[nScreenIndex], str.c_str(), str.length(), &dw, NULL);
}

void flippingBuffer()
{
	SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);
	nScreenIndex = !nScreenIndex;
}

void clearBuffer()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', screenWidth * screenHeight, Coor, &dw);
}

void deleteBuffer()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

void gotoxy(SHORT x, SHORT y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GET_HANDLE, pos);
}

void setCursor(bool visible)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 1, visible };
	SetConsoleCursorInfo(GET_HANDLE, &cursorInfo);
}