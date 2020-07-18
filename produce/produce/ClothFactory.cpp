#include "ClothFactory.h"
#include <iostream>
#include <conio.h>
#include <string>

ClothFactory::ClothFactory() : clothAmount(0), createTime(0)
{
	setWhatNumber("Cloth Factory ");
	setErrorMessage("active", "해당 건물은 이미 작동중 입니다.\n다른 번호를 선택해주세요.");
}


ClothFactory::ClothFactory(int number) : clothAmount(0), createTime(0), BaseObject(number)
{
	setWhatNumber("Cloth Factory ");
	setErrorMessage("active", "해당 건물은 이미 작동중 입니다.\n다른 번호를 선택해주세요.");
}


ClothFactory::~ClothFactory()
{
}

void ClothFactory::update(Player * player)
{
	if (checkActivate())
	{
		setCurTime();
		if (static_cast<float>(getCurTime() - getLastTime()) / CLOCKS_PER_SEC >= createTime)
		{
			setLastTime();
			player->addCloth(clothAmount);
			close();
		}
	}
}

void ClothFactory::render()
{
	// border
	setColor(LIGHT_BLUE);
	writeBuffer(getRect().x, getRect().y,				"========================================");
	writeBuffer(getRect().x, getRect().y + 1,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 2,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 3,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 4,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 5,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 6,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + 7,			"|                                      |");
	writeBuffer(getRect().x, getRect().y + getRect().h, "========================================");

	setColor(WHITE);
	writeBuffer(getRect().x + 1, getRect().y + 1, getShowNumber() + std::to_string(getNumber()));

	if (checkActivate())
	{
		writeBuffer(getRect().x + 2, getRect().y + 2,
			std::to_string(createTime - (static_cast<float>(getCurTime() - getLastTime()) / CLOCKS_PER_SEC)).substr(0, 4) + "초 남음");
	}
	else
	{
		setColor(LIGHT_RED);
		writeBuffer(getRect().x + 1, getRect().y + 2, "need -> money: " +
			std::to_string(objectCost.clothCost.money) + ", " + "fabric: " +
			std::to_string(objectCost.clothCost.fabric));
	}
}

char ClothFactory::canBuy(Player * player)
{
	if (checkActivate())
	{
		setErrorMessage("activate", "해당 건물은 이미 열려있습니다.\n다른 번호를 선택해주세요.");
		return CANT_OPEN;
	}
	else
	{
		writeBuffer(getRect().x + 1, getRect().y + 3, "제작할 옷의 개수를 입력하세요: 0");
		flippingBuffer();
		setCursor(true);
		
		std::string amount;
		amount.push_back('0');
		int key = 0;

		while (true)
		{
			gotoxy(getRect().x + 32 + amount.size(), getRect().y + 3);
			if (_kbhit())
			{
				key = _getch();
				if (key == BACKSPACE)
				{
					if (!amount.empty())
					{
						amount.pop_back();
						if (amount.empty())
							amount.push_back('0');
						writeBuffer(getRect().x + 32, getRect().y + 3, "    ");
					}
				}
				else if (key == ENTER)
				{
					clothAmount = atoi(amount.c_str());
					break;
				}
				else if (key == ESCAPE)
				{
					setErrorMessage("activate", "작동할 수 없습니다.\n\0");
					return CANT_OPEN;
				}
				else if ('0' <= key && key <= '9')
				{
					if (amount[0] == '0')
					{
						amount.pop_back();
						amount.push_back(key);
					}
					else
					{
						if (amount.length() < 4)
						{
							amount.push_back(key);
						}
					}
				}
				else
					continue;
				writeBuffer(getRect().x + 1, getRect().y + 3, "제작할 옷의 개수를 입력하세요:");
				writeBuffer(getRect().x + 32, getRect().y + 3, amount);
				flippingBuffer();
			}
			Sleep(33);
		}
		setCursor(false);

		if (player->getMoney() >= (objectCost.clothCost.money * clothAmount) && player->getFabric() >= (objectCost.clothCost.fabric * clothAmount))
		{
			player->giveMoney(objectCost.clothCost.money * clothAmount);
			player->giveFabric(objectCost.clothCost.fabric * clothAmount);
			active();
			if (clothAmount == 1)
			{
				createTime = 10;
			}
			else
			{
				createTime = (clothAmount * 14 + 100) * 0.1;
			}
			return CAN_OPEN;
		}
		else
		{
			if (player->getMoney() < objectCost.clothCost.money * clothAmount)
			{
				setErrorMessage("buy", "돈이 부족합니다.\n옷 만드는데에도 돈이 들어가요");
			}
			else if (player->getFabric() < objectCost.clothCost.fabric * clothAmount)
			{
				setErrorMessage("buy", "옷감이 부족합니다.\n옷을 만드는데 옷감을 안 들고오네ㅋ");
			}
			return CANT_BUY;
		}
	}
}