#include <iostream>
#include <iomanip>
#include <conio.h>
#include "ConsoleUI.h"

void ConsoleUI::getPlayerName()
{
	system("cls");
	vector<string>castle =
	{
		 "                                                                               ",
		 "                                  |>>>                                         ",
		 "                                  |                                            ",
		 "                    |>>>      _  _|_  _         |>>>                           ",
		 "                    |        |;| |;| |;|        |                              ",
		 "                _  _|_  _    \\\\.    .  /    _  _|_  _                          ",
		 "               |;|_|;|_|;|    \\\\:. ,  /    |;|_|;|_|;|                         ",
		 "               \\\\..      /    ||;   . |    \\\\.    .  /                         ",
		 "                \\\\.  ,  /     ||:  .  |     \\\\:  .  /                          ",
		 "                 ||:   |_   _ ||_ . _ | _   _||:   |                           ",
		 "                 ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |                           ",
		 "                 ||:   ||.    .     .      . ||:  .|                           ",
		 "                 ||: . || .     . .   .  ,   ||:   |       \\,/                 ",
		 "                 ||:   ||:  ,  _______   .   ||: , |            /`\\            ",
		 "                 ||:   || .   /+++++++\\    . ||:   |                                  ",
		 "                 ||:   ||.    |+++++++| .    ||: . |                                          ",
		 "              __ ||: . ||: ,  |+++++++|.  . _||_   |                                 O   /",
		 "     ____--`~    '--~~__|.    |+++++__|----~    ~`---,              ___             /|\\ X ",
		 "-~--~                   ~---__|,--~'                  ~~----_____-~'   `~----~~-----/ \\"
	};

	for (auto& s : castle)
	{
		for (auto& c : s)
		{
			if (c == '>') FnSetTextColor(EColors::LIGHT_RED);
			cout << c;
			FnSetTextDefault();
		}

		cout << endl;
	}
	vector<string> story =
	{
		"",
		"여긴 작은 왕국, 스파르타. 얼마 전부터 나라에 몬스터가 나타나기 시작했습니다.",
		"사람들은 불안에 떨었고 나라는 혼란에 빠졌습니다."
		"",
		"이를 해결하기 위해 모험을 나선 당신의 이름은...   "
	};
	for (int i = 0; i < story.size(); i++)
	{
		
		PrintBySpellingWithColor(story[i], EColors::LIGHT_GRAY, ETypingSpeed::FAST);
		FnSleep(300);
		if (i != story.size() - 1) cout << endl;

		while (_kbhit()) 
		{
			_getch();
		}
	}	
}

