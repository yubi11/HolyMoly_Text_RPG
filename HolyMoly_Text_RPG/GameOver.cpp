#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::gameOver()
{
	//system("cls");

	vector<string> gameover =
	{
		"",
		"",
		"",
		" _____                        _____                ",
		"|  __ \\                      |  _  |               ",
		"| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __ ",
		"| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|",
		"| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |   ",
		" \\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ",
		"",
		"",
		""
	};
	//PrintByLineWithColor(gameover, EColors::RED, ETypingSpeed::END);
	int consoleWidth = 90;
	FnSetTextColor(EColors::RED);
	for (auto& s : gameover)
	{
		int s_len = s.length();
		int padding = (consoleWidth - s_len) / 2;
		cout << setw(padding + s_len) << right << s << endl;
		FnSleep(100);
	}
	FnSetTextDefault();
	system("pause");
}