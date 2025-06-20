#pragma once
#include "common.h"

class Item;
class Character;

class Shop
{
public:
	Shop();
	void DisplayItems();
	void BuyItem(int index, Character* player);
	void SellItem(int index, Character* player);

private:
	//vector<Item*> availableItems;
	vector<unique_ptr<Item>> availableItems;
};