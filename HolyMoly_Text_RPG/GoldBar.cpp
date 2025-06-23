#include "GoldBar.h"
#include "Character.h"
#include <iostream>
using namespace std;

GoldBar::GoldBar() : name("Gold Bar"), price(50), value(50) {}

string GoldBar::getName() const { return name; }
int GoldBar::getPrice() const { return price; }
int GoldBar::getItemValue() const { return value; }
void GoldBar::use(Character* character) {
    int current = character->getGold();
    character->setGold(current +value);
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� " << value << "��带 ȹ���߽��ϴ�." << endl;
}
void GoldBar::display() const {
    cout << "[������: " << name << "] ȿ��: ��� +" << value
        << " / ����: " << price << " Gold" << endl;
}