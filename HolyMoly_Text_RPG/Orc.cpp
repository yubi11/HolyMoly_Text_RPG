#include "Orc.h"

Item* Orc::dropItem() // ���� ���Ǹ� ���� ����
{
	int randNum = getRandom(99);
	if (randNum < 30)
	{
		return new AttackBoost();
	}
	else return nullptr;
}
