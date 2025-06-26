#pragma once
#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "common.h"

class ConsoleUI 
{
public:
	static const int consoleWidth = 90;
	static void pressEnter();	// Press Enter to continue
	static void title();	// ���� Ÿ��Ʋ ȭ��
	static void getPlayerName();	// �÷��̾� �̸� �޾ƿ��� ȭ��
	static void gameOver();	// ���� ���� ȭ��
	static void gameClear();	// ���� Ŭ���� ȭ��
	static void getPlayerJob(vector<string>& job);	// �÷��̾� ���� �޾ƿ��� ȭ��
	static void displayPlayLog(vector<string>& log, int totalMonster, int level, int gold);	// ���� �÷��� �α� ��� ȭ��
	static void displayBattleResult(bool isPlayerDead, string p_name, string m_name, int level);	// ��Ʋ ��� ��� ȭ��
	static void playScene();	// ��Ʋ ���� �� ��

};
#endif // !1

