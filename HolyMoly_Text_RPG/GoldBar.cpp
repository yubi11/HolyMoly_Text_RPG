#include "GoldBar.h"
#include "Character.h"
#include <iostream>
using namespace std;

GoldBar::GoldBar() : name("Gold Bar"), price(50), value(50) {}

string GoldBar::getName() const { return name; }
int GoldBar::getPrice() const { return price; }
int GoldBar::getItemValue() const { return value; }
void GoldBar::use(Character* character) {
    int current = character->getGold();
    character->setGold(current +value);
    cout << character->getName() << "이(가) " << name << "을(를) 사용하여 " << value << "골드를 획득했습니다." << endl;
}
void GoldBar::display() const {
    cout << "[아이템: " << name << "] 효과: 골드 +" << value
        << " / 가격: " << price << " Gold" << endl;
}