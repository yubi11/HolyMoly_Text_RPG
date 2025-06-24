#include "ExpBook.h"
#include "Character.h"
#include <iostream>
using namespace std;

ExpBook::ExpBook() : name("Exp Book"), price(30), value(50) {}

string ExpBook::getName() const { return name; }
int ExpBook::getPrice() const { return price; }
int ExpBook::getItemValue() const { return value; }
void ExpBook::use(Character* character) { // Character Ŭ���� ���� addExperience �Լ��� ���� ����ġ å ������� ��� ����ġ ���� �� ������ ����ó��
    character->addExperience(value);
    cout << character->getName() << "��(��) " << name << "��(��) ����Ͽ� " << value << "����ġ�� ȹ���߽��ϴ�." << endl;
}
void ExpBook::display() const {
    cout << "[������: " << name << "] ȿ��: ����ġ +" << value
        << " / ����: " << price << " Gold" << endl;
}