#include "Store.h"
#include "setting.h"
#include <conio.h>


Store::Store() : customer(nullptr), productPrice(2), isOpen(false), sellItem(SELECT_ITEM::EMPTY)
{
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
	writeBuffer(1, 32, "판매할 물건을 선택하세요.");

	writeBuffer(3, 34, "1.product: " + std::to_string(productPrice) + "개당 1원");
}

void Store::sell(int item)
{
	switch (item)
	{
	case SELECT_ITEM::PRODUCT:
		if (customer->getProduct() >= productPrice)
		{
			customer->setProduct(productPrice);
			customer->addMoney();
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
