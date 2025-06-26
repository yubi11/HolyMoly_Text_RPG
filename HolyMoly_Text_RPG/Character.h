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
    static Character* instance; // �̱����� ���� ĳ���� ��ä �ν��Ͻ�
    string name;
    string job;
    int level;
    int health;
    int maxHealth;
    int attack;
    int experience;
    int gold;
    //vector<Item> inventory;



    map<string, pair<Item*, int>> inventory; //�������� �̸�(string)�� Ű ������ �ް� <������ ��ü�� ������, ����(int)>�� ���� ���� �κ��丮�� ���.



    // Item ��ü�� ����ϴ� �Լ�
    void useItemObject(Item* item);

    Character(string name, int jobNum);
    ~Character();
    // ���� �����ڿ� ���� �����ڸ� �����Ͽ� ���� ���� => �̱��� ���������� ���
    Character(const Character&) = delete; //���� ����
    Character& operator=(const Character&) = delete; // ���� ����

public:
    //���� �޼���: ������ ĳ���� �ν��Ͻ� ��ȯ => �̱��濡 ���� ĳ���� ��ü�� �ݵ�� �ϳ��� ������.
    static Character* getInstance(string name = "", int jobNum = 1);
    static string getInstanceName();
    static void destroyInstance();

    void displayStatus();
    void levelUp();
    void useItem(const string& item, int quantity = 1);
    void visitShop();

    // Getter �Լ�
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

    // Setter �Լ�
    void setHealth(int h);
    void setMaxHealth(int mh);
    void setAttack(int a);
    void setGold(int g);
    void setLevel(int l);
    void addExperience(int exp);
    void addItem(Item* item, int quantity = 1);
    void removeItem(const string&, int quantity = 1);
    void takeDamage(int damage);
};

#endif
