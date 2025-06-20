#pragma once
#include <iostream>

#include "Item.h"

using namespace std;

class Monster {
	Monster() {};
	Monster(int level) {};
	virtual ~Monster() {};
protected:
	string name;
	int health;
	int attack;
	
public:
	// Getter 함수
	virtual string getName() const = 0;			// 몬스터 이름
	virtual int getHealth() const = 0;			// 몬스터 체력 
	virtual int getAttack() const = 0;			// 몬스터 공격
	
	virtual void takeDamage(int damage) = 0;	// 몬스터 피해
	virtual Item* dropItem() = 0;				// 아이템 드롭
	
};

class Goblin :public Monster {};
class Orc :public Monster {};
class Troll :public Monster {};
class BossMonster :public Monster {};
