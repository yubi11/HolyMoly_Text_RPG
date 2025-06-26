#include "ExpBook.h"
#include "Character.h"
#include <iostream>
using namespace std;

ExpBook::ExpBook() : name("Exp Book"), price(30), value(50) {}

string ExpBook::getName() const { return name; }
int ExpBook::getPrice() const { return price; }
int ExpBook::getItemValue() const { return value; }
void ExpBook::use(Character* character) { // Character 클래스 내의 addExperience 함수를 통해 경험치 책 사용으로 얻는 경험치 증가 및 레벨업 동시처리
    cout << character->getName() << "이(가) " << name << "을(를) 사용하여 ";
    character->addExperience(value);
    cout << endl;
}
void ExpBook::display() const {
    cout << "[아이템: " << name << "] 효과: 경험치 +" << value
        << " / 가격: " << price << " Gold" << endl;
}