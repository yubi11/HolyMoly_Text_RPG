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
		static random_device rd;
		static mt19937 gen(rd());

		uniform_int_distribution<> dis(0, n);

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
	virtual string getName() const;			// 몬스터 이름
	virtual int getHealth() const;			// 몬스터 체력 
	virtual int getAttack() const;			// 몬스터 공격
	
	virtual void takeDamage(int damage);	// 몬스터 피해
	virtual Item* dropItem() = 0;			// 아이템 드롭
};