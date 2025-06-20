#pragma once

#include "Monster.h"

class Goblin :public Monster {
public:
	Goblin(int level) : Monster(level) {
		name = "Goblin";
	}
	Item* dropItem() override;
};
