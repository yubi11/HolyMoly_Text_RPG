#include "Monster.h"

Monster:: Monster(int level) 
{
    int randHNum = 20 + RandomUtil::GetRandomInt(0, 10);
    int randANum = 5 + RandomUtil::GetRandomInt(0, 5);

    health = level * randHNum;
    attack = level * randANum;
}

string Monster :: getName() const { return name; }			// ���� �̸�
int Monster:: getHealth() const { return health; }		    // ���� ü�� 
int Monster:: getAttack() const { return attack; }			// ���� ����

void Monster::takeDamage(int damage) { health -= damage; }	// ���� ����

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

    int randWeight = RandomUtil::GetRandomInt(1, 100);
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
