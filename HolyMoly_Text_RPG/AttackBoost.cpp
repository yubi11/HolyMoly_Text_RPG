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
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� " << value << " ���ݷ��� �����߽��ϴ�." << endl;
}
void AttackBoost::display() const {
    cout << "[������: " << name << "] ȿ��: ���ݷ� + " << value
        << " / ����: " << price << " Gold" << endl;
}