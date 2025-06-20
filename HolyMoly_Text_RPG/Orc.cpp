#include "Orc.h"

Item* Orc::dropItem() // 공격 포션만 갖고 있음
{
	int randNum = getRandom(99);
	if (randNum < 30)
	{
		return new AttackBoost();
	}
	else return nullptr;
}
