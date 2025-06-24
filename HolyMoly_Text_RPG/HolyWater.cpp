#include "HolyWater.h"
#include "Character.h"
#include <iostream>
using namespace std;

HolyWater::HolyWater() : name("Holy Water"), price(50), value(80) {}

string HolyWater::getName() const { return name; }
int HolyWater::getPrice() const { return price; }
int HolyWater::getItemValue() const { return value; }
void HolyWater::use(Character* character) {
    int currentHealth = character->getHealth();
    int currentAttack = character->getAttack();
    character->setHealth(currentHealth + value);
    character->setAttack(currentAttack + value);
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� �ູ�� �޾ҽ��ϴ�.(ü��, ���ݷ� " << value <<" ���)" << endl;
}

void HolyWater::display() const {
    cout << "[������ : " << name << "] ȿ�� : ü��, ���ݷ� +" << value
        << " / ���� : " << price << " Gold" << endl;
}