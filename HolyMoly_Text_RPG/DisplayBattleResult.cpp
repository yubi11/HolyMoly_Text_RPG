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
		result = "축하합니다! " + m_name + "을(를) 처치하고 레벨" + to_string(level) + "을 클리어했습니다.";
		FnSetTextColor(EColors::GREEN);
	}
	cout << endl << endl;

	int s_len = result.length();
	int padding = (ConsoleUI::consoleWidth - s_len) / 2;
	cout << setw(padding + s_len) << right << result << endl;

	FnSetTextDefault();
	cout << endl << endl;

	//ConsoleUI::pressEnter();

	////test용
	//if (isPlayerDead) return;
	//string answer = "";
	//cout << "상점에 방문하시겠습니까? (Y/N)";

	//while (1)
	//{
	//	getline(cin, answer);

	//	answer = toupper(answer[0]);
	//	if (answer != "Y" && answer != "N")
	//	{
	//		cout << "Y나 N을 입력하세요: ";
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
}