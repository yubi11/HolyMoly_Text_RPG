#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::gameOver()
{
	FnPlaySFX_GameOver(); // 효과음 재생
	system("cls");

	vector<string> gameover =
	{
		"\\  \\  \\     /  /  /                                         |	    ",
		" \\  \\,'`._,'`./  /                                          |	    ",
		"  \\,'`./___\\,'`./              +                          / _ \\		 ",
		"  ,'`-./_____\\,-'`.                               #      \\_\\(_)/_/	 ",
		"      /       \\                                           _//o\\\\_	 ",
		"                        #                                    /   \\	     ",
		" _____                        _____                ",
		"|  __ \\                      |  _  |               ",
		"| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __ ",
		"| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|",
		"| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |   ",
		" \\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ",
		"  _\\(O)/_	",
		"  /(_)\\",
		"#		         "
	};

	FnSetTextColor(EColors::RED);
	for (auto& s : gameover)
	{
		int s_len = s.length();
		int padding = (ConsoleUI::consoleWidth - s_len) / 2;
		cout << setw(padding + s_len) << right << s << endl;
		FnSleep(100);
	}
	FnSetTextDefault();
}