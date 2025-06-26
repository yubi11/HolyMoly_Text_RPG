#include "Goblin.h"

Goblin::Goblin(int level) : Monster(level)
{
    name = "Goblin";
    gold = RandomUtil::GetRandomInt(10, 20);
    skills = { { "몸통 박치기" , 1.0f }, { "마구 할퀴기", 1.5f} };

    InitItemPool();
}

void Goblin::InitItemPool()
{
    itemPool = {
        { ItemType::HealthPotion, 40 },
        { ItemType::AttackBoost, 40 },
        { ItemType::ExpBook, 20 }
    };
}

Item* Goblin::dropItem()
{
    return pickItem();
}


int Goblin::dropGold()
{
    return gold;
}

void Goblin::displayMonster() {
    FnPlaySFX_MonsterGoblin(); // 효과음 재생
    vector<string> MonsterAsciiArt = {
    "       ,      ,       ",
    "      /(.-\"\"-.)\\      ",
    "   |\\  \\/      \\/  /|  ",
    "   | \\ / =.  .= \\ / |   ",
    "  \\( \\   o\\/o   / )/  ",
    "   \\_, '-/  \\-' ,_/   ",
    "     /   \\__/   \\     ",
    "     \\ \\__/\\__/ /     ",
    "   ___\\ \\|--|/ /___   ",
    " /`    \\      /    `\\ ",
    " /       '----'       \\ "
    };


    int consoleWidth = 90;

    FnSetTextColor(EColors::RED);
    for (auto& s : MonsterAsciiArt)
    {
        int s_len = s.length();
        int padding = (consoleWidth - s_len) / 2;
        cout << setw(padding + s_len) << right << s << endl;
        FnSleep(100);
    }

    cout << endl;
    FnSetTextDefault();
    FnStopSFX_MonsterGoblin(); // 효과음 정지
}