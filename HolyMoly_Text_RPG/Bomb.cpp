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
    cout << character->getName() << "��(��) " << name << "��(��) ���� ������ " << value << " ���ظ� �������ϴ�." << endl;
    //monster->takeDamage(value);
}
void Bomb::display() const {
    cout << "[������: " << name << "] ȿ��: ������ + " << value << "��ŭ ���ظ� �ִ� ��ź�� �����ϴ�."
        << " / ����: " << price << " Gold" << endl;
}