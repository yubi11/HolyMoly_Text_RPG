#include "ConsoleUI.h"
#include <iostream>

void ConsoleUI::pressEnter()
{
	cout << endl;
	FnSetTextColor(EColors::LIGHT_RED);
	cout.width(consoleWidth);
	cout << "Press Enter to Continue";
	FnSetTextDefault();
	cin.get();
}