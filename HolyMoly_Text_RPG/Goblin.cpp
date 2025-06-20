#include "Goblin.h"

Item* Goblin::dropItem() // 체력 포션만 갖고 있음
{
	int randNum = getRandom(99);

	if (randNum < 30)
	{
		return new HealthPotion();
	}
	else return nullptr;
}