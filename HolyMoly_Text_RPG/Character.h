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
    ~Character();

public:
    // 복사 생성자와 대입 연산자를 삭제하여 복사 방지 => 싱글톤 디자인패턴 사용
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;
    //정적 메서드: 유일한 캐릭터 인스턴스 반환 => 싱글톤에 따라 캐릭터 객체는 반드시 하나만 존재함.
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
    void removeItem(const string&, int quantity = 1);
    void takeDamage(int damage);
};

#endif
