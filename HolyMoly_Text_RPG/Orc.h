#pragma once

#include "Monster.h"

class Orc :public Monster {
public:
	Orc(int level) : Monster(level) {
		name = "Orc";
	}
	Item* dropItem() override;
};