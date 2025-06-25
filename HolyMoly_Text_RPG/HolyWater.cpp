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
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� �ູ�� �޾ҽ��ϴ�.(ü��: " << value <<", ���ݷ�: " << value/10 << "���" << endl;
}

void HolyWater::display() const {
    cout << "[������ : " << name << "] ȿ�� : ü��, ���ݷ� +" << value
        << " / ���� : " << price << " Gold" << endl;
}