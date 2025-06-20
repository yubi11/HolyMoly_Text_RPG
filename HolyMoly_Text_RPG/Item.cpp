#include "Item.h"
#include <iostream>
using namespace std;

//HealthPotion 클래스
class HealthPotion : public Item
{
public:
    HealthPotion() : Item("Health Potion", 10, 50) {} //가격, 수치는 추후 변경 예정
    
    void use(Character* character) override {} //여기에 캐릭터 체력 회복 로직 구현 예정

    void display() const override {
        cout << "[아이템 : " << name << "] 효과 : 체력 +" << increaseAmount
             << " / 가격 : " << price << " Gold" << endl;
    }
};

//AttackBoost 클래스 구현
class AttackBoost : public Item
{
public:
    AttackBoost() : Item("Attack Boost", 15, 10) {} //가격, 수치는 추후 변경 예정
    
    void use(Character* character) override {} //여기에 캐릭터 공격력 증가 로직 구현 예정

    void display() const override {
        cout << "[아이템 : " << name << "] 효과 : 공격력 +" << increaseAmount
             << " / 가격 : " << price << " Gold" << endl;
    }
};