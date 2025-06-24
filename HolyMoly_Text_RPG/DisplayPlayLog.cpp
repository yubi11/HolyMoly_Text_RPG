#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::displayPlayLog(vector<string>& log,int totalMonster, int level, int gold) 
{
	cout << endl;
	cout << endl;
	string last = "총 처치한 몬스터: " + to_string(totalMonster)
		+ "마리 / 최종 도달한 레벨: " + to_string(level)
		+ " / 총 골드: " + to_string(gold);
	log.push_back(last);
	FnSetTextDefault();
	for (int i = 0; i < log.size(); i++)
	{
		if (i == log.size() - 1) 
		{
			cout << endl << endl;
			FnSetTextColor(EColors::YELLOW);
		}
		int s_len = log[i].length();
		int padding = (consoleWidth - s_len) / 2;
		cout << setw(padding + s_len) << right << log[i] << endl;
		FnSleep(300);
	}
	FnSetTextDefault();

	ConsoleUI::pressEnter();
	
}