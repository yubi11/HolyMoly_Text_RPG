#include "Monster.h"


string Monster :: getName() const { return name; }			// 몬스터 이름
int Monster:: getHealth() const { return health; }		    // 몬스터 체력 
int Monster:: getAttack() const { return attack; }			// 몬스터 공격

void Monster::takeDamage(int damage) { health -= damage; };	// 몬스터 피해

Item* Goblin::dropItem() // 체력 포션만 갖고 있음
{ 
	int randNum = getRandom(99);

	if (randNum < 30) 
	{
		return new HealthPotion();
	}
	else return nullptr;
}

Item* Orc::dropItem() // 공격 포션만 갖고 있음
{ 
	int randNum = getRandom(99);
	if (randNum < 30) 
	{
		return new AttackBoost();
	}
	else return nullptr;
}

Item* Troll::dropItem() // 체력, 공격 포션
{ 
	int randNum = getRandom(99);

	if (randNum < 30) 
	{
		return getRandom(1) ?  new HealthPotion() : new AttackBoost();
	}
	else return nullptr;
}

Item* BossMonster::dropItem() // 체력, 공격 포션
{
	int randNum = getRandom(99);

	if (randNum < 30)
	{
		return getRandom(1) ? new HealthPotion() : new AttackBoost();
	}
	else return nullptr;
}