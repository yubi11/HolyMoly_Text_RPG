#include "rottenMeat.h"
#include "Character.h"
#include <iostream>
using namespace std;

rottenMeat::rottenMeat() : name("rotten Meat"), price(5), value(10) {}

string rottenMeat::getName() const { return name; }
int rottenMeat::getPrice() const { return price; }
int rottenMeat::getItemValue() const { return value; }
void rottenMeat::use(Character* character) {
    int current = character->getGold();
    character->takeDamage(value);
    cout << character->getName() << "이(가) " << name << "을(를) 먹고 배탈이 나 " << value << "체력이 감소했습니다." << endl;
}
void rottenMeat::display() const {
    cout << "[아이템: " << name << "] 효과: 사용 시 체력 +" << value << "감소"
        << " / 가격: " << price << " Gold" << endl;
}