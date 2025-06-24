#include <iostream>
#include "ConsoleUI.h"

void ConsoleUI::getPlayerJob(vector<string>& job)
{
	//job =
	//{
	//	"1. 전사",
	//	"2. 탱커",
	//	"3. 상인"
	//};
	string s = "당신의 직업은...   ";
	FnSetTextColor(EColors::LIGHT_GRAY);
	PrintBySpellingWithColor(s, EColors::LIGHT_GRAY, ETypingSpeed::FAST);
	for (auto s : job)
	{
		cout << s << "    ";
	}
}