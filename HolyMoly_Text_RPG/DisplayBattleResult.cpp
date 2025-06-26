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
		result = "게임 오버. " + p_name + "이(가) 죽었습니다.";
		FnSetTextColor(EColors::RED);
	}
	else
	{
		result = m_name+"(level: " + to_string(level)+")을(를) 처치했습니다!";
		FnSetTextColor(EColors::CYAN);
	}
	cout << endl << endl;

	int s_len = result.length();
	int padding = (ConsoleUI::consoleWidth - s_len) / 2;
	cout << setw(padding + s_len) << right << result << endl;

	FnSetTextDefault();
	cout << endl << endl;
}