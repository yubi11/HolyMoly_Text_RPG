#include <iostream>
#include <map>
#include <string>
#include "Item.h"
#include "Character.h"
using namespace std;

Character* Character::instance = nullptr; // 싱글톤 패턴용 인스턴스 초기화

Character::Character(string n, int jobNum) : name(n), level(1), health(200),  // 캐릭터 클래스를 상속받는 생성자로 이름와 직업번호를 
maxHealth(200), attack(25),
experience(0), gold(0) {

    switch (jobNum) {
    case 1:
        job = "전사";
        cout << "기본 공격력이 높은 전사입니다. (직업: " << job << ")" << endl;
        attack = 40;
        break;
    case 2:
        job = "팔라딘";
        cout << "튼튼한 방패로 기본 체력이 높습니다. (직업: " << job << ")" << endl;
        maxHealth = 300;
        health = 300;
        break;
    case 3:
        job = "상인";
        cout << "기본 능력이 낮지만 많은 Gold를 가지고 시작합니다.. (직업: " << job << ")" << endl;
        attack = 20;
        maxHealth = 150;
        health = 150;
        gold = 150;
        break;
    default:
        job = "가지지 못한 자";
        cout << "잘못된 입력으로 여신의 축복을 받지 못했습니다. (직업: " << job << ")" << endl;
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
    cout << "\n=== " << name << " 상태 ===" << endl;
    cout << "직업: " << job << endl;
    cout << "레벨: " << level << endl;
    cout << "체력: " << health << "/" << maxHealth << endl;
    cout << "공격력: " << attack << endl;
    cout << "경험치: " << experience << "/100" << endl;
    cout << "골드: " << gold << endl;
    cout << "보유 아이템 종류: " << inventory.size() << endl;
    cout << endl;
}

void Character::levelUp() {
    if (experience >= 100 && level < 10) {
        level++;
        maxHealth += level * 10;
        attack += level * 3;
        health += level * 10;
        experience -= 100;
        cout << "레벨업! 현재 레벨: " << level << endl;
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

void Character::useItemObject(Item* item) { //혹시 몰라 작성
    item->use(this);
}

void Character::addItem(Item* item, int quantity) {
    if (item == nullptr) return;

    string itemName = item->getName();
    auto it = inventory.find(itemName);

    if (it != inventory.end()) {
        // 같은 이름이면 개수만 증가 (같은 효과이므로 문제없음)
        it->second.second += quantity;
        delete item; // 같은 아이템이면 새로운 포인터 삭제 (중복 방지)
    }
    else {
        // 새로운 아이템 추가
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
    else if (it != inventory.end() && it->second.second < quantity) { //보유 아이템 수량보다 많은 수 입력 시 수량 0개.
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
    //cout << name << " 체력: " << health << endl;
}

void Character::visitShop() {
    // GameManager에서 처리
}

// Getter 메서드들
string Character::getName() const { return name; }
int Character::getLevel() const { return level; }
int Character::getHealth() const { return health; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getExperience() const { return experience; }
int Character::getGold() const { return gold; }
map<string, pair<Item*, int>>& Character::getInventory() { return inventory; }

// Setter 메서드들
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
    cout << exp << " 경험치를 획득했습니다!" << endl;
    while (experience >= 100 && level < 10) {
        levelUp();
    }
}