#include "Goblin.h"

Item* Goblin::dropItem() // ü�� ���Ǹ� ���� ����
{
	int randNum = getRandom(99);

	if (randNum < 30)
	{
		return new HealthPotion();
	}
	else return nullptr;
}