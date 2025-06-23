#pragma once
#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "common.h"

class ConsoleUI 
{
public:
	static const int consoleWidth = 90;
	static void title();
	static void getPlayerName();
	static void gameOver();
	static void gameClear();
	static void displayPlayLog(vector<string>& log, int totalMonster, int level, int gold);

};
#endif // !1

