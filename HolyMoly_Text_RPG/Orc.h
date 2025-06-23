#pragma once

#include "Monster.h"

class Orc :public Monster {
public:
	Orc(int level);

	Item* dropItem() override;
	int dropGold() override;

	void displayMonster() override;
};