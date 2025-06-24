#include "Monster.h"

Monster:: Monster(int level) 
{
    this->level = level;
    int randHNum = 20 + RandomUtil::GetRandomInt(0, 20);    // 몬스터 체력 랜덤 
    int randANum = 5 + RandomUtil::GetRandomInt(0, 5);      // 몬스터 공격력 랜덤

    health = level * randHNum;  //캐릭터 레벨에 맞게 설정
    attack = level * randANum;
}

string Monster:: getName() const { return name; }		               // 몬스터 이름
int Monster:: getHealth() const { return health; }		               // 몬스터 체력 
int Monster:: getAttack() const { return attack; }			           // 몬스터 공격
string Monster:: getSkill()                                            // 몬스터 스킬
{
    int randSNum = RandomUtil::GetRandomInt(0, skills.size() - 1);
    SetAttackRandom();
    return skills[randSNum];
}

void Monster::SetAttackRandom() {
    int randANum = 5 + RandomUtil::GetRandomInt(0, 5); 
    attack = level * randANum;
}

void Monster::takeDamage(int damage) // 몬스터 피해
{
    health -= damage;
    if (health <= 0) health = 0;
}	

void Monster::InitItemPool(){}

// 아이템 랜덤 추출
Item* Monster::pickItem()
{
    int dropChance = RandomUtil::GetRandomInt(0, 99);
    if (dropChance >= 30) // 30% 확률로만 드랍
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
