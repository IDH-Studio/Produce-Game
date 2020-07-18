#include "BaseObject.h"


// constructor, destructor
BaseObject::BaseObject() : product(0), objectNumber(1), isActivate(false)
{
	rect.x = 50 + 10 - 1;
	rect.y = 14 + 4;
	rect.w = 40;
	rect.h = 8;
	lastTime = curTime = 0;
	showProduct = "Product: ";
	showNumber = "Number: ";
	errorMessage.activateError = "해당 건물은 이미 열려있습니다.\n다른 번호를 선택해주세요.";
	errorMessage.deactivateError = "해당 건물은 이미 닫혀있습니다.\n다른 번호를 선택해주세요.";
	errorMessage.buyError = "돈이 부족합니다.\n돈이나 더 모아오세요.";
	errorMessage.rangeError = "1 ~ 6사이의 번호를 입력해주세요.";
}


BaseObject::BaseObject(int number) : product(0), objectNumber(number + 1), isActivate(false)
{
	rect.x = ((number % 3) * 50 + 10) - 1;
	rect.y = ((number / 3) * 14) + 4;
	rect.w = 40;
	rect.h = 8;
	lastTime = curTime = 0;
	showProduct = "Product: ";
	showNumber = "Number: ";
	errorMessage.activateError = "해당 건물은 이미 열려있습니다.\n다른 번호를 선택해주세요.";
	errorMessage.deactivateError = "해당 건물은 이미 닫혀있습니다.\n다른 번호를 선택해주세요.";
	errorMessage.buyError = "돈이 부족합니다.\n돈이나 더 모아오세요.";
	errorMessage.rangeError = "1 ~ 6사이의 번호를 입력해주세요.";
}


BaseObject::~BaseObject()
{
	isActivate = false;
}


// protected functions
void BaseObject::setShowProduct(std::string productName)
{
	showProduct = productName + ": ";
}

void BaseObject::setWhatNumber(std::string whatNumber)
{
	showNumber.insert(0, whatNumber);
}

void BaseObject::addProduct()
{
	++product;
}

void BaseObject::setErrorMessage(std::string error, std::string message)
{
	// error : activate, deactivate, buy, range
	if (error == "activate")
	{
		errorMessage.activateError = message;
	}
	else if (error == "deactivate")
	{
		errorMessage.deactivateError = message;
	}
	else if (error == "buy")
	{
		errorMessage.buyError = message;
	}
	else if (error == "range")
	{
		errorMessage.rangeError = message;
	}
}

std::string BaseObject::getErrorMessage(std::string error)
{
	// error : activate, deactivate, buy, range
	if (error == "activate")
	{
		return errorMessage.activateError;
	}
	else if (error == "deactivate")
	{
		return errorMessage.deactivateError;
	}
	else if (error == "buy")
	{
		return errorMessage.buyError;
	}
	else if (error == "range")
	{
		return errorMessage.rangeError;
	}
}


clock_t BaseObject::getCurTime()
{
	return curTime;
}

void BaseObject::setCurTime()
{
	curTime = clock();
}

clock_t BaseObject::getLastTime()
{
	return lastTime;
}

void BaseObject::setLastTime()
{
	lastTime = clock();
}


OBJECT_RECT BaseObject::getRect()
{
	return rect;
}


std::string BaseObject::getShowNumber()
{
	return showNumber;
}

std::string BaseObject::getShowProduct()
{
	return showProduct;
}


// public functions
void BaseObject::active()
{
	product = 0;
	lastTime = clock();
	isActivate = true;
}

void BaseObject::active(int number)
{
	product = 0;
	objectNumber = number;
	rect.x = ((number % 3) * 50 + 10) - 1;
	rect.y = ((number / 3) * 14) + 4;
	rect.w = 40;
	rect.h = 8;
	lastTime = clock();
	isActivate = true;
}

bool BaseObject::close()
{
	if (isActivate)
	{
		isActivate = false;
		return true;
	}
	else
	{
		return false;
	}
}

void BaseObject::showError(SHORT x, SHORT y, std::string error)
{
	// error : activate, deactivate, buy, range
	if (error == "activate")
	{
		setColor(LIGHT_CYAN);
		writeBuffer(x, y, errorMessage.activateError.substr(0, errorMessage.activateError.find('\n')));
		writeBuffer(x, y + 1, errorMessage.activateError.substr(errorMessage.activateError.find('\n') + 1));
	}
	else if (error == "deactivate")
	{
		setColor(LIGHT_CYAN);
		writeBuffer(x, y, errorMessage.activateError.substr(0, errorMessage.deactivateError.find('\n')));
		writeBuffer(x, y + 1, errorMessage.activateError.substr(errorMessage.deactivateError.find('\n') + 1));
	}
	else if (error == "buy")
	{
		setColor(LIGHT_CYAN);
		writeBuffer(x, y, errorMessage.buyError.substr(0, errorMessage.buyError.find('\n')));
		setColor(RED);
		writeBuffer(x, y + 1, errorMessage.buyError.substr(errorMessage.buyError.find('\n') + 1));
	}
	else if (error == "range")
	{
		setColor(LIGHT_CYAN);
		writeBuffer(x, y, errorMessage.rangeError);
	}
}


void BaseObject::update(Player* player)
{
	/*if (isActivate)
	{
		curTime = clock();
		if (static_cast<float>(curTime - lastTime) / CLOCKS_PER_SEC >= 2)
		{
			lastTime = clock();
			++product;
			player->addProduct();
		}
	}*/
}

void BaseObject::render()
{
	//// border
	//writeBuffer(rect.x, rect.y,			 "========================================");
	//writeBuffer(rect.x, rect.y + 1,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 2,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 3,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 4,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 5,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 6,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + 7,		 "|                                      |");
	//writeBuffer(rect.x, rect.y + rect.h, "========================================");

	//if (isActivate)
	//{
	//	writeBuffer(rect.x + 1, rect.y + 1, showNumber + std::to_string(objectNumber));
	//	writeBuffer(rect.x + 1, rect.y + 2, showProduct + std::to_string(product));
	//}
	//else
	//{
	//	
	//}
}

// getter
bool BaseObject::checkActivate()
{
	return isActivate;
}


int BaseObject::getProduct()
{
	return product;
}

int BaseObject::getNumber()
{
	return objectNumber;
}