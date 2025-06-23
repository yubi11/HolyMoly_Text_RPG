#include <iostream>
#include <iomanip>
#include "ConsoleUI.h"

void ConsoleUI::getPlayerName()
{
	//system("cls");
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
		"여긴 작은 왕국, 브렌델. 얼마 전부터 나라에 몬스터가 나타나기 시작했습니다.",
		"사람들은 불안에 떨었고 나라는 혼란에 빠졌습니다."
		"",
		"이를 해결하기 위해 모험을 나선 당신의 이름은...   "
	};
	for (int i = 0; i < story.size(); i++)
	{
		PrintBySpellingWithColor(story[i], EColors::LIGHT_GRAY, ETypingSpeed::FAST);
		FnSleep(300);
		if (i != story.size() - 1) cout << endl;
	}

	// 이름입력은 StartGame에서 하기

	//string name;
	//FnSetTextColor(EColors::LIGHT_CYAN);

	//getline(cin, name);

	//cout << castle[castle.size() - 3].size() << endl;



}

