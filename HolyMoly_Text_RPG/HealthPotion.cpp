#include "HealthPotion.h"
#include <iostream>
using namespace std;

HealthPotion::HealthPotion() : name("Health Potion"), price(10), increaseAmount(50) {}

string HealthPotion::getName() { return name; }
int HealthPotion::getPrice() { return price; }
int HealthPotion::getIncreaseAmount() { return increaseAmount; }
void HealthPotion::use(Character* character) {
    // 캐릭터 체력 회복 로직 구현 예정
}
void HealthPotion::display() const {
    cout << "[아이템 : " << name << "] 효과 : 체력 +" << increaseAmount
         << " / 가격 : " << price << " Gold" << endl;