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
    character->setAttack(currentAttack + (value/5));
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� �ູ�� �޾ҽ��ϴ�.(ü��: " << value <<", ���ݷ�: " << value/5 << "���" << endl;
}

void HolyWater::display() const {
    cout << "[������ : " << name << "] ȿ�� : ü�� + "<< value << ", ���ݷ� + " << value/5
        << " / ���� : " << price << " Gold" << endl;
}