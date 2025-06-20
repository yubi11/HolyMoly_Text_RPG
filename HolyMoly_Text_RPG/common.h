#pragma once
#include <iostream>
#include <istream>
#include <regex> // 정규표현식

#include <vector>
#include <string>
#include <sstream>
#include <map>

#include <cmath>
#include <algorithm>

#include <cctype>   // isdigit
#include <limits>   // numeric_limits

#include <windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <conio.h>

#include <memory>

using namespace std;

namespace COMMON
{
    // 목록 - 씬
    enum class EScenes
    {
        Intro,  // 0
        Start,  // 1
        END = 999
    };

    // 목록 - 텍스트 컬러 정보
    enum class EColors
    {
        BLACK,          // 0
        BLUE,           // 1
        GREEN,          // 2
        CYAN,           // 3
        RED,            // 4
        MAGENTA,        // 5
        YELLOW,         // 6
        LIGHT_GRAY,     // 7
        DARK_GRAY,      // 8
        LIGHT_BLUE,     // 9
        LIGHT_GREEN,    // 10
        LIGHT_CYAN,     // 11
        LIGHT_RED,      // 12
        LIGHT_MAGENTA,  // 13
        LIGHT_YELLOW,   // 14
        WHITE,          // 15
        END = 999
    };

    // 커서 숨기기
    inline void FnHideCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    // 커서 표시
    inline void FnShowCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    // 간격 애니메이션 효과
    inline void FnSleep(int _milliseconds)
    {
        this_thread::sleep_for(chrono::milliseconds(_milliseconds));
    }

    // 텍스트 컬러 변경
    inline void FnSetTextColor(const COMMON::EColors& _Color)
    {
        if (EColors::END != _Color)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(_Color));
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(EColors::WHITE));
        }
    }

    // 텍스트 컬러 기본색 복구
    inline void FnSetTextDefault()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(EColors::WHITE));
    }

    // 문자열 입력값으로 정수 판별 확인
    inline bool FnIsNumber(const std::string& s)
    {
        std::regex pattern("^-?\\d+(\\.\\d+)?$"); // 정수 또는 실수
        return std::regex_match(s, pattern);
    }
}

using namespace COMMON;
