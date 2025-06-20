#pragma once

#include "Monster.h"

class BossMonster :public Monster {
	int power = 1.5;
public:
	BossMonster(int level) : Monster(level* power) {
		name = "BossMonster";
	}
	Item* dropItem() override;
};