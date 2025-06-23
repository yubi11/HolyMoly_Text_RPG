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
		"���� ���� �ձ�, �귻��. �� ������ ���� ���Ͱ� ��Ÿ���� �����߽��ϴ�.",
		"������� �Ҿȿ� ������ ����� ȥ���� �������ϴ�."
		"",
		"�̸� �ذ��ϱ� ���� ������ ���� ����� �̸���...   "
	};
	for (int i = 0; i < story.size(); i++)
	{
		PrintBySpellingWithColor(story[i], EColors::LIGHT_GRAY, ETypingSpeed::FAST);
		FnSleep(300);
		if (i != story.size() - 1) cout << endl;
	}

	// �̸��Է��� StartGame���� �ϱ�

	//string name;
	//FnSetTextColor(EColors::LIGHT_CYAN);

	//getline(cin, name);

	//cout << castle[castle.size() - 3].size() << endl;



}

