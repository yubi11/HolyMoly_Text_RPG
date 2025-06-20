#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Character {
private:
    static Character* instance;
    string name;
    int level;
    int health;
    int maxHealth;
    int attack;
    int experience;
    int gold;
    vector<Item> inventory;

    Character(string name);

public:
    static Character* getInstance(string name = "");

    void displayStatus();
    void levelUp();
    void useItem(int index);
    void visitShop();

    // Getter 메서드들
    string getName() const;
    int getLevel() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttack() const;
    int getExperience() const;
    int getGold() const;
    vector<Item>& getInventory();

    // Setter 메서드들
    void setHealth(int h);
    void setAttack(int a);
    void setGold(int g);
    void addExperience(int exp);
    void addItem(const Item& item);
    void removeItem(int index);
    void takeDamage(int damage);
};

#endif
