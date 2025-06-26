#include "BossMonster.h"

BossMonster::BossMonster(int level) : Monster(level) {
    name = "BossMonster";
    gold = RandomUtil::GetRandomInt(50, 200);
    skills = { { "파이어 브레스" , 2.0f }, { "꼬리 휘두르기", 1.5f}, { "꼬리 휘두르기", 1.5f} };

    health *= power;
    //attack *= power;
}

Item* BossMonster::dropItem()
{
    return pickItem(); // 전체 랜덤
}

int BossMonster::dropGold()
{
    return gold;
}

void BossMonster::displayMonster() {
    FnPlaySFX_MonsterBoss(); // 효과음 재생
    vector<string> MonsterAsciiArt = {
    "                              )      (                                ",
    "                        /+++=))    ((=+++\\                          ",
    "                  /++++++++//      \\\\+++++++++\\                   ",
    "              /++++++++++//(  /\\  )\\\\++++++++++\\               ",
    "           /+++++++++++//  \\\\^^//  \\\\+++++++++++\\            ",
    "        _/++++++++++++//  {{@::@}}  \\\\++++++++++++\\_         ",
    "      /+++++++++++++((     {\\/}     ))+++++++++++++\\        ",
    "   /+++++++++++++++\\\\    <**>    //+++++++++++++++\\     ",
    "  /+++++++++++++++++\\\\  / VV \\  //+++++++++++++++++\\    ",
    " /+++++++++++++++++++\\\\/******\\//+++++++++++++++++++\\   ",
    "|+/|++++++++++/\\++++++(***/\\***)++++++/\\++++++++++|/+\\ ",
    "|/ |+/\\+/\\+/\\/  \\+/\\++\\**|**|**/++/\\+/  \\/\\+/\\+/+| \\| ",
    "v  |/  V  V  V   V  \\+\\|*|**|*|/+/  V   v  V  V  \\|  v ",
    "      v                   /*|*|**|*|*\\...              v       ",
    "                         (**|*|**|*|**). .                     ",
    "                        __\\*|*|**|*|*/__. .                    ",
    "                       (vvv(VVV)(VVV)vvv). .                   ",
    "                         ............../ /                  ",
    "                        / ............../                   ",
    "                        ((                                          "
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
    FnStopSFX_MonsterBoss(); // 효과음 정지
}