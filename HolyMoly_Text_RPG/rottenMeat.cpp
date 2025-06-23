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
    cout << character->getName() << "��(��) " << name << "��(��) �԰� ��Ż�� �� " << value << "ü���� �����߽��ϴ�." << endl;
}
void rottenMeat::display() const {
    cout << "[������: " << name << "] ȿ��: ��� �� ü�� +" << value << "����"
        << " / ����: " << price << " Gold" << endl;
}