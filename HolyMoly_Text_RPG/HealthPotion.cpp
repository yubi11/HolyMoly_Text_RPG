#include "HealthPotion.h"
#include "Character.h"
#include <iostream>
using namespace std;

HealthPotion::HealthPotion() : name("Health Potion"), price(10), value(50) {}

string HealthPotion::getName() const { return name; }
int HealthPotion::getPrice() const { return price; }
int HealthPotion::getItemValue() const { return value; }
void HealthPotion::use(Character* character) {
    int current = character->getHealth();
    character->setHealth(current + value);
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� " << value << " ü���� ȸ���߽��ϴ�." << endl;
}

void HealthPotion::display() const {
    cout << "[������ : " << name << "] ȿ�� : ü�� + " << value
        << " / ���� : " << price << " Gold" << endl;
}