#pragma once
#include "Item.h"
using namespace std;

class ExpBook : public Item
{
private:
    string name;
    int price;
    int value;
public:
    ExpBook();
    string getName() const override;
    int getPrice() const override;
    int getItemValue() const override;
    void use(Character* character) override;
    void display() const override;
};