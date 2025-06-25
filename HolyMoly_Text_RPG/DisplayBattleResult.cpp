#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::displayBattleResult(bool isPlayerDead, string p_name, string m_name, int level)
{
	/*system("cls");*/
	FnSleep(300);
	string result;

	if (isPlayerDead)
	{
		result = "���� ����. " + p_name + "��(��) �׾����ϴ�.";
		FnSetTextColor(EColors::RED);
	}
	else
	{
		result = m_name+"(level: " + to_string(level)+")��(��) óġ�߽��ϴ�!";
		FnSetTextColor(EColors::CYAN);
	}
	cout << endl << endl;

	int s_len = result.length();
	int padding = (ConsoleUI::consoleWidth - s_len) / 2;
	cout << setw(padding + s_len) << right << result << endl;

	FnSetTextDefault();
	cout << endl << endl;
}