#include <iostream>
#include <map>
#include <string>
#include "Item.h"
#include "Character.h"
using namespace std;

Character* Character::instance = nullptr; // �̱��� ���Ͽ� �ν��Ͻ� �ʱ�ȭ

Character::Character(string n, int jobNum) : name(n), level(1), health(200),  // ĳ���� Ŭ������ ��ӹ޴� �����ڷ� �̸��� ������ȣ�� 
maxHealth(200), attack(25),
experience(0), gold(0) {

    switch (jobNum) {
    case 1:
        job = "����";
        cout << "�⺻ ���ݷ��� ���� �����Դϴ�. (����: " << job << ")" << endl;
        attack = 40;
        break;
    case 2:
        job = "�ȶ��";
        cout << "ưư�� ���з� �⺻ ü���� �����ϴ�. (����: " << job << ")" << endl;
        maxHealth = 300;
        health = 300;
        break;
    case 3:
        job = "����";
        cout << "�⺻ �ɷ��� ������ ���� Gold�� ������ �����մϴ�.. (����: " << job << ")" << endl;
        attack = 20;
        maxHealth = 150;
        health = 150;
        gold = 150;
        break;
    default:
        job = "������ ���� ��";
        cout << "�߸��� �Է����� ������ �ູ�� ���� ���߽��ϴ�. (����: " << job << ")" << endl;
        health = 100;
        maxHealth = 100;
        attack = 15;
        break;
    }
        
}

Character* Character::getInstance(string name, int jobNum) {
    if (instance == nullptr) {
        if (name.empty()) {
            name = "Unknown";
        }
        instance = new Character(name, jobNum);
    }
    return instance;
}

void Character::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

Character::~Character() {
    for (auto& item : inventory) {
        delete item.second.first;
    }
    inventory.clear();
}

string Character::getInstanceName() {
    if (instance != nullptr) {
        return instance->getName();
    }
    return "";
}

void Character::displayStatus() {
    cout << "\n=== " << name << " ���� ===" << endl;
    cout << "����: " << job << endl;
    cout << "����: " << level << endl;
    cout << "ü��: " << health << "/" << maxHealth << endl;
    cout << "���ݷ�: " << attack << endl;
    cout << "����ġ: " << experience << "/100" << endl;
    cout << "���: " << gold << endl;
    cout << "���� ������ ����: " << inventory.size() << endl;
    cout << endl;
}

void Character::levelUp() {
    if (experience >= 100 && level < 10) {
        level++;
        maxHealth += level * 10;
        attack += level * 3;
        health += level * 10;
        experience -= 100;
        cout << "������! ���� ����: " << level << endl;
    }
}

void Character::useItem(const string& itemName, int quantity) {
    auto it = inventory.find(itemName);
    if (it != inventory.end() && it->second.second >= quantity) {
        for (int i = 0; i < quantity; i++) {
            it->second.first->use(this);
        }
        it->second.second -= quantity;
        if (it->second.second == 0) {
            delete it->second.first;
            inventory.erase(it);
        }
    };
}

void Character::useItemObject(Item* item) { //Ȥ�� ���� �ۼ�
    item->use(this);
}

void Character::addItem(Item* item, int quantity) {
    if (item == nullptr) return;

    string itemName = item->getName();
    auto it = inventory.find(itemName);

    if (it != inventory.end()) {
        // ���� �̸��̸� ������ ���� (���� ȿ���̹Ƿ� ��������)
        it->second.second += quantity;
        delete item; // ���� �������̸� ���ο� ������ ���� (�ߺ� ����)
    }
    else {
        // ���ο� ������ �߰�
        inventory[itemName] = make_pair(item, quantity);
    }
}

int Character::getItemCount(const string& itemName) {
    auto it = inventory.find(itemName);
    return (it != inventory.end()) ? it->second.second : 0;
}

void Character::removeItem(const string& itemName, int quantity) {
    auto it = inventory.find(itemName);
    if (it != inventory.end() && it->second.second >= quantity) {
        it->second.second -= quantity;
    }
    else if (it != inventory.end() && it->second.second < quantity) { //���� ������ �������� ���� �� �Է� �� ���� 0��.
        it->second.second = 0;
    }
    if (it->second.second == 0) {
        delete it->second.first;
        inventory.erase(it);
    }
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    //cout << name << " ü��: " << health << endl;
}

void Character::visitShop() {
    // GameManager���� ó��
}

// Getter �޼����
string Character::getName() const { return name; }
int Character::getLevel() const { return level; }
int Character::getHealth() const { return health; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getExperience() const { return experience; }
int Character::getGold() const { return gold; }
map<string, pair<Item*, int>>& Character::getInventory() { return inventory; }

// Setter �޼����
void Character::setHealth(int h) {
    health = h;
    if (health > maxHealth) health = maxHealth;
}

void Character::setAttack(int a) { attack = a; }
void Character::setGold(int g) { gold = g; }
void Character::setLevel(int l) { level = l; }
void Character::setMaxHealth(int mh) { maxHealth = mh; }

void Character::addExperience(int exp) {
    experience += exp;
    cout << exp << " ����ġ�� ȹ���߽��ϴ�!" << endl;
    while (experience >= 100 && level < 10) {
        levelUp();
    }
}