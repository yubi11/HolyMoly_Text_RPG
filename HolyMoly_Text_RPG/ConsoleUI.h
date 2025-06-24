#pragma once
#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "common.h"

class ConsoleUI 
{
public:
	static const int consoleWidth = 90;
	static void pressEnter();
	static void title();
	static void getPlayerName();
	static void gameOver();
	static void gameClear();
	static void getPlayerJob(vector<string>& job);
	static void displayPlayLog(vector<string>& log, int totalMonster, int level, int gold);
	static void displayBattleResult(bool isPlayerDead, string p_name, string m_name, int level);

};
#endif // !1

