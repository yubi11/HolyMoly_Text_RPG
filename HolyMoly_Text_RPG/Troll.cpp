#include "Troll.h"

Item* Troll::dropItem() // ü��, ���� ����
{
	int randNum = getRandom(99);

	if (randNum < 30)
	{
		return getRandom(1) ? new HealthPotion() : new AttackBoost();
	}
	else return nullptr;
}
