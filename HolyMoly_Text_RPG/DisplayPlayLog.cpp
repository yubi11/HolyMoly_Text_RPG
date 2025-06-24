#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::displayPlayLog(vector<string>& log,int totalMonster, int level, int gold) 
{
	cout << endl;
	cout << endl;
	string last = "�� óġ�� ����: " + to_string(totalMonster)
		+ "���� / ���� ������ ����: " + to_string(level)
		+ " �� ���: " + to_string(gold);
	log.push_back(last);
	FnSetTextDefault();
	for (auto s : log)
	{
		int s_len = s.length();
		int padding = (consoleWidth - s_len) / 2;
		cout << setw(padding + s_len) << right << s << endl;
		FnSleep(300);
	}

	ConsoleUI::pressEnter();
	
}