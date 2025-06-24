#pragma once
#include "Item.h"
using namespace std;

class rottenMeat : public Item
{
private:
    string name;
    int price;
    int value;
public:
    rottenMeat();
    string getName() const override;
    int getPrice() const override;
    int getItemValue() const override;
    void use(Character* character) override;
    void display() const override;
};