#include "ClothFactory.h"
#include <iostream>
#include <conio.h>
#include <string>

ClothFactory::ClothFactory() : clothAmount(0), createTime(0)
{
	setWhatNumber("Cloth Factory ");
	setErrorMessage("active", "�ش� �ǹ��� �̹� �۵��� �Դϴ�.\n�ٸ� ��ȣ�� �������ּ���.");
}


ClothFactory::ClothFactory(int number) : clothAmount(0), createTime(0), BaseObject(number)
{
	setWhatNumber("Cloth Factory ");
	setErrorMessage("active", "�ش� �ǹ��� �̹� �۵��� �Դϴ�.\n�ٸ� ��ȣ�� �������ּ���.");
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
			std::to_string(createTime - (static_cast<float>(getCurTime() - getLastTime()) / CLOCKS_PER_SEC)).substr(0, 4) + "�� ����");
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
		setErrorMessage("activate", "�ش� �ǹ��� �̹� �����ֽ��ϴ�.\n�ٸ� ��ȣ�� �������ּ���.");
		return CANT_OPEN;
	}
	else
	{
		writeBuffer(getRect().x + 1, getRect().y + 3, "������ ���� ������ �Է��ϼ���: 0");
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
					setErrorMessage("activate", "�۵��� �� �����ϴ�.\n\0");
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
				writeBuffer(getRect().x + 1, getRect().y + 3, "������ ���� ������ �Է��ϼ���:");
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
				setErrorMessage("buy", "���� �����մϴ�.\n�� ����µ����� ���� ����");
			}
			else if (player->getFabric() < objectCost.clothCost.fabric * clothAmount)
			{
				setErrorMessage("buy", "�ʰ��� �����մϴ�.\n���� ����µ� �ʰ��� �� �����פ�");
			}
			return CANT_BUY;
		}
	}
}