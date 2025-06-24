#include "Orc.h"

Orc::Orc(int level) : Monster(level) {
	name = "Orc Mage";
	gold = RandomUtil::GetRandomInt(7, 15);
}

Item* Orc::dropItem()
{
	return pickItem(ItemType::AttackBoost);
}


int Orc::dropGold()
{
	return gold;
}

void Orc::displayMonster() {
    vector<string> MonsterAsciiArt = {
    "  ,    ,    /\\   /\\",
    "  /( /\\ )\\  _\\ \\_/ /_",
    "  |\\_||_/| < \\_   _/ >",
    "  \\______/  \\|0   0|/",
    "    _\\/_   _(_  ^  _)_",
    "     ( () ) /`\\|V\"\"\"V|/`\\",
    "       {}   \\  \\_____/  /",
    "       ()   /\\   )=(   /\\",
    "        {}  /  \\_/\\=/\\_/  \\"
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