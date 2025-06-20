#include "Shop.h"

#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

Shop::Shop()
{
	availableItems.push_back(make_unique<HealthPotion>());
	availableItems.push_back(make_unique<AttackBoost>());
}

void Shop::DisplayItems()
{

	// 텍스트 컬러 변경
	FnSetTextColor(EColors::YELLOW);
	string strWelcome = "상점에 오신 것을 환영합니다!\n구매 가능한 아이템:\n";
	for (int i = 0; i < strWelcome.length(); i++)
	{
		std::cout << strWelcome[i];
		FnSleep(10);
	}
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();

	string strItem = "";
	int idx = 1;
	//for (const Item* item : availableItems)
	for (const std::unique_ptr<Item>& itemPtr : availableItems)
	{
		strItem += idx++;
		strItem += " ";
		strItem += itemPtr->getName();
		strItem += "(체력+";
		strItem += itemPtr->getIncreseAmount();
		strItem += "): ";
		strItem += itemPtr->getPrice();
		strItem += " 골드";
		strItem += ",";
	}
}

void Shop::BuyItem(int index, Character* player)
{
}

void Shop::SellItem(int index, Character* player)
{
}
