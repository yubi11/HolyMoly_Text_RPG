#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::displayPlayLog(vector<string>& log,int totalMonster, int level, int gold) 
{
	//PrintByLineWithColor(log, EColors::WHITE, ETypingSpeed::FAST);
	string last = "총 처치한 몬스터: " + to_string(totalMonster)
		+ "마리 / 최종 도달한 레벨: " + to_string(level)
		+ " 총 골드: " + to_string(gold);
	FnSetTextDefault();
	for (auto s : log) 
	{
		int s_len = s.length();
		int padding = (consoleWidth - s_len) / 2;
		cout << setw(padding + s_len) << right << s << endl;
		FnSleep(100);
	}
	
}