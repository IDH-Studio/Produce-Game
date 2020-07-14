#include "Store.h"
#include "setting.h"
#include <conio.h>


Store::Store() : customer(nullptr), isOpen(false), sellItem(SELECT_ITEM::EMPTY)
{
	// ������ ��
	quantity.product = 2;
	quantity.fiber = 2;
	// ���� ��
	price.product = 10;
	price.fiber = 10;
}


Store::~Store()
{
	customer = nullptr;
}

void Store::visit(Player* player)
{
	customer = player;
	isOpen = true;
}

void Store::update()
{
	int key;
	if (_kbhit())
	{
		key = _getch();

		if (inputError != INPUT_ERROR::NONE)
		{
			inputError = INPUT_ERROR::NONE;
		}
		else
		{
			if (key == ESCAPE)
			{
				this->out();
			}
			else
			{
				if ('1' <= key && key <= '9')
				{
					this->sell(key % '0');
				}
				else
				{
					inputError = INPUT_ERROR::RANGE;
				}
			}
		}
	}
}

void Store::render()
{
	writeBuffer(1, 32, "�Ǹ��� ������ �����ϼ���.");

	writeBuffer(3, 34, "1.product: " + std::to_string(quantity.product) + "���� " + std::to_string(price.product) + "��");
	writeBuffer(3, 35, "2.fiber: " + std::to_string(quantity.fiber) + "���� " + std::to_string(price.fiber) + "��");
}

void Store::sell(int item)
{
	switch (item)
	{
	case SELECT_ITEM::PRODUCT:
		if (customer->getProduct() >= quantity.product)
		{
			customer->giveProduct(quantity.product);
			customer->receiveMoney(price.product);
		}
		break;
	case SELECT_ITEM::FIBER:
		if (customer->getFiber() >= quantity.fiber)
		{
			customer->giveFiber(quantity.fiber);
			customer->receiveMoney(price.fiber);
		}
		break;
	}
}

void Store::out()
{
	customer = nullptr;
	isOpen = false;
}

bool Store::isOpened()
{
	return isOpen;
}
