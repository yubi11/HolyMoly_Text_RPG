#include "ChaosOrb.h"
#include "Character.h"
#include <iostream>
#include "RandomUtil.h"
using namespace std;

ChaosOrb::ChaosOrb() : name("Chaos Orb"), price(50), value(0) {}

string ChaosOrb::getName() const { return name; }
int ChaosOrb::getPrice() const { return price; }
int ChaosOrb::getItemValue() const { return value; }
void ChaosOrb::use(Character* character) {
    int MaxHealth = RandomUtil::GetRandomInt(10, 400);
    int Health = RandomUtil::GetRandomInt(1, 400);
    int Attack = RandomUtil::GetRandomInt(1, 100);
    int Gold = RandomUtil::GetRandomInt(0, 300);
    //int Level = RandomUtil::GetRandomInt(1, 9);
    character->setMaxHealth(MaxHealth);
    character->setHealth(Health);
    character->setAttack(Attack);
    character->setGold(Gold);
    //character->setLevel(Level);
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� ȥ���� ������ ���� ��� �ɷ�ġ�� ��ȭ�߽��ϴ�." << endl;
    character->displayStatus();
}
void ChaosOrb::display() const {
    cout << "[������: " << name << "] ȿ��: ��� �ɷ�ġ ������ ��ȭ"
        << " / ����: " << price << " Gold" << endl;
}