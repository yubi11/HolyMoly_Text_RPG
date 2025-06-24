#include "Monster.h"

Monster:: Monster(int level) 
{
    this->level = level;
    int randHNum = 20 + RandomUtil::GetRandomInt(0, 20);    // ���� ü�� ���� 
    int randANum = 5 + RandomUtil::GetRandomInt(0, 5);      // ���� ���ݷ� ����

    health = level * randHNum;  //ĳ���� ������ �°� ����
    attack = level * randANum;
}

string Monster:: getName() const { return name; }		               // ���� �̸�
int Monster:: getHealth() const { return health; }		               // ���� ü�� 
int Monster:: getAttack() const { return attack; }			           // ���� ����
string Monster:: getSkill()                                            // ���� ��ų
{
    int randSNum = RandomUtil::GetRandomInt(0, skills.size() - 1);
    SetAttackRandom();
    return skills[randSNum];
}

void Monster::SetAttackRandom() {
    int randANum = 5 + RandomUtil::GetRandomInt(0, 5); 
    attack = level * randANum;
}

void Monster::takeDamage(int damage) // ���� ����
{
    health -= damage;
    if (health <= 0) health = 0;
}	

void Monster::InitItemPool(){}

// ������ ���� ����
Item* Monster::pickItem()
{
    int dropChance = RandomUtil::GetRandomInt(0, 99);
    if (dropChance >= 30) // 30% Ȯ���θ� ���
        return nullptr;

    //int totalWeight = 0;
    //for (const auto& item : itemPool)
    //    totalWeight += item.weight;

    int randWeight = RandomUtil::GetRandomInt(0, 100);
    int sum = 0;

    for (const auto& item : itemPool)
    {
        sum += item.weight;
        if (randWeight <= sum)
        {
            switch (item.type)
            {
            case ItemType::HealthPotion:
                return new HealthPotion();

            case ItemType::AttackBoost:
                return new AttackBoost();

            case ItemType::ExpBook:
                return new ExpBook();

            case ItemType::GoldBar:
                return new GoldBar();

            case ItemType::HolyWater:
                return new HolyWater();

            case ItemType::rottenMeat:
                return new rottenMeat();

            default:
                return nullptr;
            }
        }
    }

    return nullptr;
}
