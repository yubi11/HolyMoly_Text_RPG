#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <map>
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
    //vector<Item> inventory;
    map<string, pair<Item*, int>> inventory;

    // Item 객체를 사용하는 함수
    void useItemObject(Item* item);

    Character(string name);

public:
    static Character* getInstance(string name = "");
    static string getInstanceName();

    void displayStatus();
    void levelUp();
    void useItem(const string& item, int quantity = 1);
    void visitShop();

    // Getter 함수
    string getName() const;
    int getLevel() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttack() const;
    int getExperience() const;
    int getGold() const;
    int getItemCount(const string& itemName);
    //vector<Item>& getInventory();
    map<string, pair<Item*, int>>& getInventory();

    // Setter 함수
    void setHealth(int h);
    void setAttack(int a);
    void setGold(int g);
    void addExperience(int exp);
    void addItem(Item* item, int quantity = 1);
    void removeItem(const string&);
    void takeDamage(int damage);
};

#endif
