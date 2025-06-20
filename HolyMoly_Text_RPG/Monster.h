#pragma once
#include <iostream>
#include <random>

#include "Item.h"

using namespace std;

class Monster {
protected:
	string name;
	int health = 0;
	int attack = 0;


	int getRandom(int n) { // 1부터 n 까지 랜덤
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<> dis(0, n);

		return dis(gen);
	}
	
public:
	Monster() {};
	Monster(int level) {
		int randHNum = 20 + getRandom(10);
		int randANum = 5 + getRandom(5);

		health = level * randHNum;
		attack = level * randANum;
	};
	virtual ~Monster() {};

	// Getter 함수
	virtual string getName() const;		// 몬스터 이름
	virtual int getHealth() const;	// 몬스터 체력 
	virtual int getAttack() const;		// 몬스터 공격
	
	virtual void takeDamage(int damage);	// 몬스터 피해
	virtual Item* dropItem() = 0;				// 아이템 드롭
	
};

class Goblin :public Monster {
public:
	Goblin(int level) : Monster(level) {
		name = "Goblin";
	}
	Item* dropItem() override;
};

class Orc :public Monster {
public:
	Orc(int level) : Monster(level) {
		name = "Orc";
	}
	Item* dropItem() override;
};

class Troll :public Monster {
public:
	Troll(int level) : Monster(level) {
		name = "Troll";
	}
	Item* dropItem() override;
};

class BossMonster :public Monster {
	int power = 1.5;
public:
	BossMonster(int level) : Monster(level * power) {
		name = "BossMonster";
	}
	Item* dropItem() override;
};
