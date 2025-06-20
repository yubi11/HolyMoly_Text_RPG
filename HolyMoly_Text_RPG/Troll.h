#pragma once

#include "Monster.h"

class Troll :public Monster {
public:
	Troll(int level) : Monster(level) {
		name = "Troll";
	}
	Item* dropItem() override;
};