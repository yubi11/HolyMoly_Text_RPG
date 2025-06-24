#pragma once

#include "Monster.h"

class Troll :public Monster {
public:
	Troll(int level);

	Item* dropItem() override;
	int dropGold() override;

	void displayMonster() override;

};