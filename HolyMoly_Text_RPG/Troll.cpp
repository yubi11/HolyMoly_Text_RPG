#include "Troll.h"

Troll::Troll(int level) : Monster(level) {
    name = "Troll";
    gold = RandomUtil::GetRandomInt(5, 15);
    skills = { { "몸통 박치기" , 1.0f }, { "물어 뜯기", 1.5f} };
}

Item* Troll::dropItem()  // 체력, 공격 포션
{
    return pickItem(); // 전체 랜덤
}

int Troll::dropGold()
{
    return gold;
}

void Troll::displayMonster() {
    FnPlaySFX_MonsterTroll(); // 효과음 재생
    vector<string> MonsterAsciiArt = {
"       ,   .-'''=;_   ",
"      |\\.'-~`-.`-`;/|",
"      \\.` '.'~-.` './",
"     (\\`,__=-'__,'/)",
"       _.-'-.( d\_/b ).-'-._ ",
"      /'.-'   ' .---. '   '-.`\\ ",
"       /'  .' (=    (_)    =) '.  `\\ ",
"      /'  .',  `-.__.-.__.-'  ,'.  `\\ ",
"     (     .'.   V       V  ; '.     )",
"     (    |::  `-,__.-.__,-'  ::|    )",
"     |   /|`:.               .:'|\\   |",
"     |  / | `:.              :' |`\\  |",
"     | |  (  :.             .:  )  | |",
"     | |   ( `:.            :' )   | |",
"     | |    \\ :.           .: /    | |",
"     | |     \\`:.         .:'/     | |",
"     ) (      `\\`:.     .:'/'      ) (",
"     (  `)_     ) `:._.:' (     _(`  )",
"     \\  ' _)  .'           `.  (_ `  /",
"      \\  '_) /   .''```''.   \\ (_`  /",
    "     `''`  \\  (         )  /  `''`",
    "       ___   ___  `.`.       .'.'        ___",
    "     .`   `````'''--`_)     (_'--'''`````   `.",
    "     (_(_(___...--'''`         `'''--...___)_)_)"

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
    FnStopSFX_MonsterTroll(); // 효과음 정지
}