﻿#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::gameClear()
{
	FnPlaySFX_GameClear(); // 효과음 재생

	system("cls");

	//vector<string>gameclear =
	//{
	//	 "                                                   _____                        _____ _                     ",
	//	 "                          |>>>               +    |  __ \\         +            /  __ \\ |                 ",
	//	 "                          |                       | |  \\/ __ _ _ __ ___   ___  | /  \\/ | ___  __ _ _ __   ",
	//	 "            |>>>      _  _|_  _         |>>>      | | __ / _` | '_ ` _ \\ / _ \\ | |   | |/ _ \\/ _` | '__| ",
	//	 "       +    |        |;| |;| |;|        |         | |_\\ \\ (_| | | | | | |  __/ | \\__/\\ |  __/ (_| | |   ",
	//	 "        _  _|_  _    \\\\.    .  /    _  _|_  _      \\____/\\__,_|_| |_| |_|\\___|  \\____/_|\\___|\\__,_|_| ",
	//	 "       |;|_|;|_|;|    \\\\:. ,  /    |;|_|;|_|;|                         ",
	//	 "       \\\\..      /    ||;   . |    \\\\.    .  /                                               *",
	//	 "        \\\\.  ,  /     ||:  .  |     \\\\:  .  /                   *       ",
	//	 "         ||:   |_   _ ||_ . _ | _   _||:   |            *                         +",
	//	 "         ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |                    +       ",
	//	 "         ||:   ||.    .     .      . ||:  .|                                             * ",
	//	 "         ||: . || .     . .   .  ,   ||:   |       \\,/                 ",
	//	 "         ||:   ||:  ,  _______   .   ||: , |            /`\\                     *",
	//	 "         ||:   || .   /+++++++\\    . ||:   |                                                    * ",
	//	 "         ||:   ||.    |+++++++| .    ||: . |          +              *                  ",
	//	 "      __ ||: . ||: ,  |+++++++|.  . _||_   |                                \\O/  ",
	//	 "_--`~    '--~~__|.    |+++++__|----~    ~`---,              ___              |                 ___",
	//	 "                ~---__|,--~'                  ~~----_____-~'   `~----~~-----/ \\ ~~----_____-~'   `~----~~-----"
	//};
	vector<string>gameclear =
	{
		 "                                                 _____                          ",
		 "                        |>>>               +    |  __ \\         +            ",
		 "                        |                       | |  \\/ __ _ _ __ ___   ___  ",
		 "          |>>>      _  _|_  _         |>>>      | | __ / _` | '_ ` _ \\ / _ \\ ",
		 "     +    |        |;| |;| |;|        |         | |_\\ \\ (_| | | | | | |  __/    ",
		 "      _  _|_  _    \\\\.    .  /    _  _|_  _      \\____/\\__,_|_| |_| |_|\\___|  ",
		 "     |;|_|;|_|;|    \\\\:. ,  /    |;|_|;|_|;|                         ",
		 "     \\\\..      /    ||;   . |    \\\\.    .  /                  _____ _  ",
		 "      \\\\.  ,  /     ||:  .  |     \\\\:  .  /             *    /  __ \\ | ",
		 "       ||:   |_   _ ||_ . _ | _   _||:   |      *            | /  \\/ | ___  __ _ _ __  ",
		 "       ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |              +    | |   | |/ _ \\/ _` | '__| ",
		 "       ||:   ||.    .     .      . ||:  .|                   | \\__/\\ |  __/ (_| | |   ",
		 "       ||: . || .     . .   .  ,   ||:   |    \\,/             \\____/_|\\___|\\__,_|_| ",
		 "       ||:   ||:  ,  _______   .   ||: , |            /`\\                     *",
		 "       ||:   || .   /+++++++\\    . ||:   |                                       * ",
		 "       ||:   ||.    |+++++++| .    ||: . |          +              *                  ",
		 "    __ ||: . ||: ,  |+++++++|.  . _||_   |                              \\O/  ",
		 "-`~    '--~~__|.    |+++++__|----~    ~`---,              ___            |               ",
		 "              ~---__|,--~'                  ~~----_____-~'   `~----~~---/ \\ ~~----___-~'"
	};
	PrintByLineWithColor(gameclear, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
}