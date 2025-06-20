#pragma once
#include <string>
using namespace std;

class Character;

class Item
{
private:
	string name;
	int value;

public:
	virtual ~Item() {}

	virtual string getName() = 0;             	// 아이템 이름
	virtual int getPrice() = 0;               	// 아이템 가격
	virtual int getIncreaseAmount() = 0;       	// 효과 수치 (회복량, 공격력 등)
	virtual void use(Character* character) = 0; // 캐릭터에게 아이템 사용
	virtual void display() const = 0;			// 아이템 정보 콘솔에 출력
};

class HealthPotion;
Class AttackBoost;
