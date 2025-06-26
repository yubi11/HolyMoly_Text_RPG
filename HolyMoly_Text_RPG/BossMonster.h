#pragma once

#include "Monster.h"

class BossMonster :public Monster {
	int power = 2;
public:
	BossMonster(int level);

	Item* dropItem() override;
	int dropGold() override;

	void displayMonster() override;
};