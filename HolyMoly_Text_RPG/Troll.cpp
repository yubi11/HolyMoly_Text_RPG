#include "Troll.h"

Troll::Troll (int level) : Monster(level) {
	name = "Troll";
	gold = RandomUtil::GetRandomInt(5, 15);
    skills = { "���� ��ġ��" , "���� ���" };
}

Item* Troll::dropItem()  // ü��, ���� ����
{
	return pickItem(); // ��ü ����
}

int Troll::dropGold()
{
	return gold;
}

void Troll::displayMonster() {
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
}