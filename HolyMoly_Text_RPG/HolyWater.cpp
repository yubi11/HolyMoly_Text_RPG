#include "HolyWater.h"
#include "Character.h"
#include <iostream>
using namespace std;

HolyWater::HolyWater() : name("Holy Water"), price(100), value(200) {}

string HolyWater::getName() const { return name; }
int HolyWater::getPrice() const { return price; }
int HolyWater::getItemValue() const { return value; }
void HolyWater::use(Character* character) {
    int currentHealth = character->getHealth();
    int currentAttack = character->getAttack();
    character->setHealth(currentHealth + value);
    character->setAttack(currentAttack + (value/10));
    cout << character->getName() << "이(가) " << name << "을(를) 사용하여 축복을 받았습니다.(체력: " << value <<", 공격력: " << value/10 << "상승" << endl;
}

void HolyWater::display() const {
    cout << "[아이템 : " << name << "] 효과 : 체력, 공격력 +" << value
        << " / 가격 : " << price << " Gold" << endl;
}