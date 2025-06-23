#include "AttackBoost.h"
#include <iostream>
using namespace std;

AttackBoost::AttackBoost() : name("Attack Boost"), price(15), increaseAmount(10) {}

string AttackBoost::getName() { return name; }
int AttackBoost::getPrice() { return price; }
int AttackBoost::getIncreaseAmount() { return increaseAmount; }
void AttackBoost::use(Character* character) {
    // 캐릭터 공격력 증가 로직 구현 예정
}
void AttackBoost::display() const {
    cout << "[아이템: " << name << "] 효과: 공격력 +" << increaseAmount
        << " / 가격: " << price << " Gold" << endl;
}