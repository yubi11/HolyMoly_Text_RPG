//#include <iostream>
//#include <string>
//#include <vector>
//#include <thread>
//#include <chrono>
//#include <iomanip>
//#include "ConsoleUI.h"
//#include "RandomUtil.h"
//using namespace std;
//
//const int screenWidth = 90;
//const int scrollSpeedMs = 100;
//const int messageFrame1 = 15;
//const int messageFrame2 = 25;
//const int messageFrame3 = 32;
//
//
//
//vector<string> bg = {
//    "        _    .  ,   .           .                      ",
//    "    *  / \\_ *  / \\_      _  *        *   /\\'__        *",
//    "      /    \\  /    \\,   ((        .    _/  /  \\  *'.   ",
//    " .   /\\/\\  /\\/ :' __ \\_  `          _^/  ^/    `--.    ",
//    "    /    \\/  \\  _/  \\-'\\      *    /.' ^_   \\_   .'\\  *",
//    "  /\\  .-   `. \\/     \\ /==~=-=~=-=-;.  _/ \\ -. `_/   \\ ",
//    " /  `-.__ ^   / .-'.--\\ =-=~_=-=~=^/  _ `--./ .-'  `-  ",
//    "/        `.  / /       `.~-^=-=~=^=.-'      '-._ `._   "
//};
//
//void drawFrame(int frame) {
//    // 콘솔 화면 초기화 (지운 것처럼 보이게)
//    system("cls");  // Windows 전용
//    cout << string(3, '\n');
//    // 배경 출력
//    FnSetTextColor(EColors::DARK_GRAY);
//    for (const auto& line : bg) {
//        string extended = line + "   " + line + "   " + line; // 반복
//        int start = frame % line.size();
//        cout << extended.substr(start, screenWidth) << endl;
//    }
//
//    // 메시지 출력 (배경 바로 아래에)
//    cout << endl;
//    FnSetTextDefault();
//    if (frame <= messageFrame1) {
//        cout << RandomUtil::fillSides("...주변이 조용해졌다...", screenWidth, ' ') << endl;
//    }
//    else if (frame <= messageFrame2) {
//        cout << RandomUtil::fillSides("...어딘가에서 기척이 느껴진다...", screenWidth, ' ') << endl;
//    }
//    else if (frame <= messageFrame3) {
//        cout << RandomUtil::fillSides("야생의 몬스터가 나타났다!", screenWidth, ' ') << endl;
//    }
//}
//
//void ConsoleUI::playScene()
//{
//    int frame = 0;
//    drawFrame(frame);
//    FnPlaySFX_PlayScene();  // 효과음 재생
//    while (true) {
//        this_thread::sleep_for(chrono::milliseconds(scrollSpeedMs));
//        frame++;
//
//        if (frame > messageFrame3)
//        {
//            FnStopSFX_PlayScene(); // 효과음 정지
//            break;
//        }
//    }
//}

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

// TODO : 메모리 누수
//------------------------------------------------------------
static string msg1 = RandomUtil::fillSides("...주변이 조용해졌다...", screenWidth, ' ');
static string msg2 = RandomUtil::fillSides("...어딘가에서 기척이 느껴진다...", screenWidth, ' ');
static string msg3 = RandomUtil::fillSides("야생의 몬스터가 나타났다!", screenWidth, ' ');
//------------------------------------------------------------

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
    FnMoveCursorToTop();  // 화면 지우지 않고 맨 위로 이동
    cout << string(3, '\n');

    FnSetTextColor(EColors::DARK_GRAY);
    //for (const auto& line : bg) {
    //    string extended = line + "   " + line + "   " + line;   // TODO : 메모리 누수
    //    int start = frame % line.size();
    //    cout << extended.substr(start, screenWidth) << endl;    // TODO : 메모리 누수
    //}
    //------------------------------------------------------------
    for (const auto& line : bg)
    {

        static const string separator = "   ";
        const string& segment = line;

        // stiring에 "+" 연산자 누적 시 누수 문제 해결 : 긴 문자열을 직접 반복 출력 (substr 없음)
        string extended;
        extended.reserve(segment.size() * 3 + separator.size() * 2);
        extended.append(segment);
        extended.append(separator);
        extended.append(segment);
        extended.append(separator);
        extended.append(segment);

        int start = frame % segment.size();  // 스크롤 시작 위치

        // substr 누수 문제 해결 : substr() 대신 범위 직접 출력
        for (int i = 0; i < screenWidth; ++i)
        {
            char ch = extended[start + i];
            cout.put(ch);
        }
        cout << '\n';
    }
    //------------------------------------------------------------

    cout << endl;
    FnSetTextDefault();
    // TODO : 메모리 누수
    //if (frame <= messageFrame1) {
    //    cout << RandomUtil::fillSides("...주변이 조용해졌다...", screenWidth, ' ') << endl;
    //}
    //else if (frame <= messageFrame2) {
    //    cout << RandomUtil::fillSides("...어딘가에서 기척이 느껴진다...", screenWidth, ' ') << endl;
    //}
    //else if (frame <= messageFrame3) {
    //    cout << RandomUtil::fillSides("야생의 몬스터가 나타났다!", screenWidth, ' ') << endl;
    //}
    //------------------------------------------------------------
    if (frame <= messageFrame1)
    {
        cout << msg1 << endl;
    }
    else if (frame <= messageFrame2)
    {
        cout << msg2 << endl;
    }
    else if (frame <= messageFrame3)
    {
        cout << msg3 << endl;
    }
    //------------------------------------------------------------
}

void ConsoleUI::playScene() {
    int frame = 0;
    FnPlaySFX_PlayScene();  // 효과음 재생
    system("cls");          // 화면 지우기
    FnHideCursor();         // 커서 숨기기

    // 콘솔 출력 버퍼 크기 조정 (깜빡임 방지 및 내용 숨기기 위함)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    SMALL_RECT windowSize = csbi.srWindow;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { screenWidth, 100 });

    while (true) {
        drawFrame(frame);
        this_thread::sleep_for(chrono::milliseconds(scrollSpeedMs));
        frame++;

        if (frame > messageFrame3) {
            FnStopSFX_PlayScene();  // 효과음 정지
            break;
        }
    }

    FnShowCursor();  // 끝난 후 커서 다시 보이기
}
