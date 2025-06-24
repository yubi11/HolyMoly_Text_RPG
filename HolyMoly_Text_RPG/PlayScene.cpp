#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include "ConsoleUI.h"
#include "RandomUtil.h"
using namespace std;

const int screenWidth = 90;
const int scrollSpeedMs = 100;
const int messageFrame1 = 20;
const int messageFrame2 = 40;
const int messageFrame3 = 60;



vector<string> bg = {
    "        _    .  ,   .           .                      ",
    "    *  / \\_ *  / \\_      _  *        *   /\\'__        *",
    "      /    \\  /    \\,   ((        .    _/  /  \\  *'.   ",
    " .   /\\/\\  /\\/ :' __ \\_  `          _^/  ^/    `--.    ",
    "    /    \\/  \\  _/  \\-'\\      *    /.' ^_   \\_   .'\\  *",
    "  /\\  .-   `. \\/     \\ /==~=-=~=-=-;.  _/ \\ -. `_/   \\ ",
    " /  `-.__ ^   / .-'.--\\ =-=~_=-=~=^/  _ `--./ .-'  `-  ",
    "/        `.  / /       `.~-^=-=~=^=.-'      '-._ `._   "
};

void drawFrame(int frame) {
    // �ܼ� ȭ�� �ʱ�ȭ (���� ��ó�� ���̰�)
    system("cls");  // Windows ����
    cout << string(3, '\n');
    // ��� ���
    FnSetTextColor(EColors::DARK_GRAY);
    for (const auto& line : bg) {
        string extended = line + "   " + line + "   " + line; // �ݺ�
        int start = frame % line.size();
        cout << extended.substr(start, screenWidth) << endl;
    }

    // �޽��� ��� (��� �ٷ� �Ʒ���)
    cout << endl;
    FnSetTextDefault();
    if (frame <= messageFrame1) {
        cout << RandomUtil::fillSides("...�ֺ��� ����������...", screenWidth, ' ') << endl;
    }
    else if (frame <= messageFrame2) {
        cout << RandomUtil::fillSides("...��򰡿��� ��ô�� ��������...", screenWidth, ' ') << endl;
    }
    else if (frame <= messageFrame3) {
        cout << RandomUtil::fillSides("�߻��� ���Ͱ� ��Ÿ����!", screenWidth, ' ') << endl;
    }
}

void ConsoleUI::playScene()
{
    int frame = 0;

    while (true) {
        drawFrame(frame);

        this_thread::sleep_for(chrono::milliseconds(scrollSpeedMs));
        frame++;

        if (frame > messageFrame3) break;
    }
}


