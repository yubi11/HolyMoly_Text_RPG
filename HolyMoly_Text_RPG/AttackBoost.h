#pragma once
#include "Item.h"
using namespace std;

class AttackBoost : public Item
{
private:
    string name;
    int price;
    int increaseAmount;

public:
    AttackBoost();
    string getName() override;
    int getPrice() override;
    int getIncreaseAmount() override;
    void use(Character* character) override;
    void display() const override;
};