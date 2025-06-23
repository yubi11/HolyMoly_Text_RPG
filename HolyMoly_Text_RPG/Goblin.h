#pragma once

#include "Monster.h"

class Goblin :public Monster { 
public:
	Goblin(int level);

	Item* dropItem() override;
	int dropGold() override;

	void displayMonster() override;
};
