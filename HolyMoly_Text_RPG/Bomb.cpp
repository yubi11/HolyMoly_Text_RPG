#include "Bomb.h"
#include "Character.h"
#include "Monster.h"
#include <iostream>
using namespace std;

Bomb::Bomb() : name("Bomb"), price(15), value(10) {}

string Bomb::getName() const { return name; }
int Bomb::getPrice() const { return price; }
int Bomb::getItemValue() const { return value; }
void Bomb::use(Character* character) {
    cout << character->getName() << "이(가) " << name << "을(를) 던져 적에게 " << value << " 피해를 입혔습니다." << endl;
    //monster->takeDamage(value);
}
void Bomb::display() const {
    cout << "[아이템: " << name << "] 효과: 적에게 + " << value << "만큼 피해를 주는 폭탄을 던집니다."
        << " / 가격: " << price << " Gold" << endl;
}