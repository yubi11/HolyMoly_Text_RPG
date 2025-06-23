#include "Orc.h"

Orc::Orc(int level) : Monster(level) {
	name = "Orc";
	gold = RandomUtil::GetRandomInt(7, 15);
}

Item* Orc::dropItem()
{
	return pickItem(ItemType::AttackBoost);
}


int Orc::dropGold()
{
	return gold;
}