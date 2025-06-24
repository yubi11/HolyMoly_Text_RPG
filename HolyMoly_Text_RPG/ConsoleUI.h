#pragma once
#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "common.h"

class ConsoleUI 
{
public:
	static const int consoleWidth = 90;
	static void pressEnter();	// Press Enter to continue
	static void title();	// 게임 타이틀 화면
	static void getPlayerName();	// 플레이어 이름 받아오는 화면
	static void gameOver();	// 게임 오버 화면
	static void gameClear();	// 게임 클리어 화면
	static void getPlayerJob(vector<string>& job);	// 플레이어 직업 받아오는 화면
	static void displayPlayLog(vector<string>& log, int totalMonster, int level, int gold);	// 최종 플레이 로그 출력 화면
	static void displayBattleResult(bool isPlayerDead, string p_name, string m_name, int level);	// 배틀 결과 출력 화면
	static void playScene();	// 배틀 시작 전 씬

};
#endif // !1

