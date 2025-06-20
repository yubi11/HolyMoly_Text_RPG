#include "Monster.h"

string Monster :: getName() const { return name; }			// 몬스터 이름
int Monster:: getHealth() const { return health; }		    // 몬스터 체력 
int Monster:: getAttack() const { return attack; }			// 몬스터 공격

void Monster::takeDamage(int damage) { health -= damage; };	// 몬스터 피해
