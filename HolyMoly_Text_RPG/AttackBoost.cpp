#include "AttackBoost.h"
#include "Character.h"
#include <iostream>
using namespace std;

AttackBoost::AttackBoost() : name("Attack Boost"), price(15), value(10) {}

string AttackBoost::getName() const { return name; }
int AttackBoost::getPrice() const { return price; }
int AttackBoost::getItemValue() const { return value; }
void AttackBoost::use(Character* character) {
    int current = character->getAttack();
    character->setAttack(current + value);
    cout << character->getName() << "이(가) " << name << "을(를) 사용하여 " << value << " 공격력이 증가했습니다." << endl;
}
void AttackBoost::display() const {
    cout << "[아이템: " << name << "] 효과: 공격력 + " << value
        << " / 가격: " << price << " Gold" << endl;
}