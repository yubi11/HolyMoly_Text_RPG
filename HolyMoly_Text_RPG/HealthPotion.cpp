#include "HealthPotion.h"
#include "Character.h"
#include <iostream>
using namespace std;

HealthPotion::HealthPotion() : name("Health Potion"), price(10), value(50) {}

string HealthPotion::getName() const { return name; }
int HealthPotion::getPrice() const { return price; }
int HealthPotion::getItemValue() const { return value; }
void HealthPotion::use(Character* character) {
    int current = character->getHealth();
    character->setHealth(current + value);
    cout << character->getName() << "이(가) " << name << "을(를) 사용하여 " << value << " 체력을 회복했습니다." << endl;
}

void HealthPotion::display() const {
    cout << "[아이템 : " << name << "] 효과 : 체력 + " << value
        << " / 가격 : " << price << " Gold" << endl;
}