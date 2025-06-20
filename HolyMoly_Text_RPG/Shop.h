#pragma once
#include "common.h"
#include "Item.h"

class Character;

class Shop
{
public:
	Shop();

	// 상점 진입
	void OnEnter(Character* player);

	// 표시 - 판매중인 아이템 목록
	void DisplayItems(Character* player);

	// 구매
	void BuyItem(Character* player);

	// 판매
	void SellItem(Character* player);

private:

	// 판매중인 아이템
	vector<unique_ptr<Item>> availableItems;
	//vector<Item*> availableItems;
};