#pragma once
#include <iostream>
#include <iomanip>

#include "RandomUtil.h"
#include "common.h"

#include "HealthPotion.h"
#include "AttackBoost.h"

using namespace std;

class Monster {
protected:
	string name;
	int health = 0;
	int attack = 0;
	int gold = 0;

	enum class ItemType {
		HealthPotion = 0,
		AttackBoost = 1
	};

public:
	Monster() {};
	Monster(int level);
	virtual ~Monster() {};

	// Getter 함수
	string getName() const;					// 몬스터 이름
	int getHealth() const;					// 몬스터 체력 
	int getAttack() const;					// 몬스터 공격
	
	virtual void takeDamage(int damage);	// 몬스터 피해

	Item* pickItem();						// 아이템 랜덤 추출
	Item* pickItem(ItemType Item);
	Item* pickItem(ItemType beginItem, ItemType endItem);		

	virtual Item* dropItem() = 0;			// 아이템 드롭
	virtual int dropGold() = 0;				// 골드 드롭

	virtual void displayMonster() = 0;		// 몬스터 아스키 아트
};