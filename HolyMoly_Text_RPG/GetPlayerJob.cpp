#include <iostream>
#include "ConsoleUI.h"

void ConsoleUI::getPlayerJob(vector<string>& job)
{
	//job =
	//{
	//	"1. ����",
	//	"2. ��Ŀ",
	//	"3. ����"
	//};
	string s = "����� ������...   ";
	FnSetTextColor(EColors::LIGHT_GRAY);
	PrintBySpellingWithColor(s, EColors::LIGHT_GRAY, ETypingSpeed::FAST);
	for (auto s : job)
	{
		cout << s << "    ";
	}
}