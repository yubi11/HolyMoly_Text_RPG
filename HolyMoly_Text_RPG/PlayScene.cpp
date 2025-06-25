﻿#include <iostream>
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
const int messageFrame1 = 15;
const int messageFrame2 = 25;
const int messageFrame3 = 32;



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
    // 콘솔 화면 초기화 (지운 것처럼 보이게)
    system("cls");  // Windows 전용
    cout << string(3, '\n');
    // 배경 출력
    FnSetTextColor(EColors::DARK_GRAY);
    for (const auto& line : bg) {
        string extended = line + "   " + line + "   " + line; // 반복
        int start = frame % line.size();
        cout << extended.substr(start, screenWidth) << endl;
    }

    // 메시지 출력 (배경 바로 아래에)
    cout << endl;
    FnSetTextDefault();
    if (frame <= messageFrame1) {
        cout << RandomUtil::fillSides("...주변이 조용해졌다...", screenWidth, ' ') << endl;
    }
    else if (frame <= messageFrame2) {
        cout << RandomUtil::fillSides("...어딘가에서 기척이 느껴진다...", screenWidth, ' ') << endl;
    }
    else if (frame <= messageFrame3) {
        cout << RandomUtil::fillSides("야생의 몬스터가 나타났다!", screenWidth, ' ') << endl;
    }
}

void ConsoleUI::playScene()
{
    int frame = 0;
    drawFrame(frame);
    FnPlaySFX_PlayScene();  // 효과음 재생
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(scrollSpeedMs));
        frame++;

        if (frame > messageFrame3)
        {
            FnStopSFX_PlayScene(); // 효과음 정지
            break;
        }
    }
}