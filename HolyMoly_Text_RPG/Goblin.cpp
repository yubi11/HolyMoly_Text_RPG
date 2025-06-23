#include "Goblin.h"

Goblin::Goblin(int level) : Monster(level) {
	name = "Goblin";
    gold = RandomUtil::GetRandomInt(5, 10);
}

Item* Goblin::dropItem() 
{
	return pickItem(ItemType::HealthPotion);
}


int Goblin::dropGold()
{
	return gold;
}

void Goblin::displayMonster() {
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
}