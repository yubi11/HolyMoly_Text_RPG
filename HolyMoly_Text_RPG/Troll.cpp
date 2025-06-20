#include "Troll.h"

Item* Troll::dropItem() // 체력, 공격 포션
{
	int randNum = getRandom(99);

	if (randNum < 30)
	{
		return getRandom(1) ? new HealthPotion() : new AttackBoost();
	}
	else return nullptr;
}
