#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

#include "RandomUtil.h"
#include "common.h"

#include "HealthPotion.h"
#include "AttackBoost.h"
#include "ExpBook.h"
#include "GoldBar.h"
#include "HolyWater.h"
#include "rottenMeat.h"
#include "Bomb.h"

using namespace std;

class Monster {
protected:
	string name = "";
	int health = 0;
	int attack = 0;
	int gold = 0;
	int level = 1;

	vector<string> skills = { "몸통 박치기" };

	enum class ItemType {
		HealthPotion = 0,
		AttackBoost = 1,
		ExpBook = 2,
		GoldBar = 3,
		HolyWater = 4,
		rottenMeat = 5
	};

	struct WeightedItem {
		ItemType type;
		int weight;
	};

	// 기본 드랍 아이템 구성 (자식에서 InitItemPool() 호출 시 덮어씌워짐)
	vector<WeightedItem> itemPool = {
		{ ItemType::HolyWater, 1 },       // 1%
		{ ItemType::GoldBar, 5 },         // 5%
		{ ItemType::ExpBook, 5 },         // 5%
		{ ItemType::AttackBoost, 14 },    // 14%
		{ ItemType::HealthPotion, 15 },   // 15%
		{ ItemType::rottenMeat, 60 }	  // 60%
	};


public:
	Monster() {};
	Monster(int level);
	virtual ~Monster() {};

	// Getter 함수
	string getName() const;					// 몬스터 이름
	int getHealth() const;					// 몬스터 체력 
	int getAttack() const;					// 몬스터 공격
	string getSkill(vector<string> skills = {});					// 몬스터 스킬

	// Setter 함수
	void SetAttackRandom();

	virtual void takeDamage(int damage = 0);	// 몬스터 피해

	Item* pickItem();						// 아이템 랜덤 추출
	virtual void InitItemPool();			// 아이템 목록
	virtual Item* dropItem() = 0;			// 아이템 드롭
	virtual int dropGold() = 0;				// 골드 드롭

	virtual void displayMonster() = 0;		// 몬스터 아스키 아트
};