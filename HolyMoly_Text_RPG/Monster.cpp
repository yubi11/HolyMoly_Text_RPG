#include "Monster.h"

Monster:: Monster(int level) 
{
    int randHNum = 20 + RandomUtil::GetRandomInt(0, 10);
    int randANum = 5 + RandomUtil::GetRandomInt(0, 5);

    health = level * randHNum;
    attack = level * randANum;
}

string Monster :: getName() const { return name; }			// 몬스터 이름
int Monster:: getHealth() const { return health; }		    // 몬스터 체력 
int Monster:: getAttack() const { return attack; }			// 몬스터 공격

void Monster::takeDamage(int damage) { health -= damage; }	// 몬스터 피해

// 아이템 랜덤 추출
Item* Monster::pickItem() {
    return pickItem(ItemType::HealthPotion, ItemType::AttackBoost);
}

Item* Monster::pickItem(ItemType itemOne) {
    return pickItem(itemOne, itemOne);
}

Item* Monster::pickItem(ItemType beginItem, ItemType endItem)
{
    int randNum = RandomUtil::GetRandomInt(0, 99);

    if (randNum < 30) // 30% 확률로 드랍
    {
        ItemType itemType;

        if (beginItem == endItem)
        {
            itemType = beginItem;
        }
        else
        {
            int min = static_cast<int>(beginItem);
            int max = static_cast<int>(endItem);

            int randItemNum = RandomUtil::GetRandomInt(min, max);
            itemType = static_cast<ItemType>(randItemNum);
        }

        switch (itemType)
        {
        case ItemType::HealthPotion:
            return new HealthPotion();

        case ItemType::AttackBoost:
            return new AttackBoost();

        default:
            return nullptr;
        }
    }
}
