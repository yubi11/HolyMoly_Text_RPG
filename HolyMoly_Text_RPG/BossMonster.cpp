#include "BossMonster.h"

BossMonster::BossMonster(int level) : Monster(level) {
	name = "BossMonster";
	gold = RandomUtil::GetRandomInt(25, 50);
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
    "   v                   /*|*|**|*|*\\...              v       ",
    "                      (**|*|**|*|**). .                     ",
    "                     __\\*|*|**|*|*/__. .                    ",
    "                    (vvv(VVV)(VVV)vvv). .                   ",
    "                      ............../ /                  ",
    "                     / ............../                   ",
    "                     ((                                          "
    };


	int consoleWidth = 90;

	FnSetTextColor(EColors::RED);
	for (auto& s : MonsterAsciiArt)
	{
		int s_len = s.length();
		int padding = (consoleWidth - s_len);
		cout << setw(padding + s_len) << right << s << endl;
		FnSleep(100);
	}

	cout << endl;
	FnSetTextDefault();
}