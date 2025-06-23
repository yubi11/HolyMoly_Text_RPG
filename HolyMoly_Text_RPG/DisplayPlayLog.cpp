#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::displayPlayLog(vector<string>& log,int totalMonster, int level, int gold) 
{
	//PrintByLineWithColor(log, EColors::WHITE, ETypingSpeed::FAST);
	string last = "�� óġ�� ����: " + to_string(totalMonster)
		+ "���� / ���� ������ ����: " + to_string(level)
		+ " �� ���: " + to_string(gold);
	FnSetTextDefault();
	for (auto s : log) 
	{
		int s_len = s.length();
		int padding = (consoleWidth - s_len) / 2;
		cout << setw(padding + s_len) << right << s << endl;
		FnSleep(100);
	}
	
}