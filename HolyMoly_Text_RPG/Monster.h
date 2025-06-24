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

	vector<string> skills = { "���� ��ġ��" };

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

	// �⺻ ��� ������ ���� (�ڽĿ��� InitItemPool() ȣ�� �� �������)
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

	// Getter �Լ�
	string getName() const;					// ���� �̸�
	int getHealth() const;					// ���� ü�� 
	int getAttack() const;					// ���� ����
	string getSkill(vector<string> skills = {});					// ���� ��ų

	// Setter �Լ�
	void SetAttackRandom();

	virtual void takeDamage(int damage = 0);	// ���� ����

	Item* pickItem();						// ������ ���� ����
	virtual void InitItemPool();			// ������ ���
	virtual Item* dropItem() = 0;			// ������ ���
	virtual int dropGold() = 0;				// ��� ���

	virtual void displayMonster() = 0;		// ���� �ƽ�Ű ��Ʈ
};