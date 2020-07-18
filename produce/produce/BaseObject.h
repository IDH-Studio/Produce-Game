#pragma once
#include <time.h>
#include <string>
#include <Windows.h>
#include "Player.h"
#include "setting.h"

#define CAN_OPEN 0b00000001
#define CANT_OPEN 0b00000010
#define CANT_BUY 0b00000100

typedef struct
{
	int x;
	int y;
	int w;
	int h;
}OBJECT_RECT;

class BaseObject
{
private:
	int product;
	int objectNumber;
	bool isActivate;
	clock_t curTime, lastTime;
	OBJECT_RECT rect;
	std::string showProduct, showNumber;
	struct ErrorMessage errorMessage;
protected:
	void setShowProduct(std::string productName);
	void setWhatNumber(std::string whatNumber);
	void setErrorMessage(std::string error, std::string message);
	std::string getErrorMessage(std::string error);
	
	void addProduct();
	
	clock_t getCurTime();
	void setCurTime();
	clock_t getLastTime();
	void setLastTime();
	
	OBJECT_RECT getRect();
	
	std::string getShowNumber();
	std::string getShowProduct();
public:
	BaseObject();
	BaseObject(int number);
	~BaseObject();

	void active();
	void active(int number);
	bool close();
	void showError(SHORT x, SHORT y, std::string error);

	virtual void update(Player* player) = 0;
	virtual void render() = 0;
	virtual char canBuy(Player* player) = 0;

	// getter
	bool checkActivate();
	int getProduct();
	int getNumber();
};