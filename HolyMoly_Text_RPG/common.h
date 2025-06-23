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

/*
    공통
*/
namespace COMMON
{
    //static const int INF = numeric_limits<int>::max();    // 사용하고 싶은데 에러 발생중

    // 목록 - 씬(화면)을 구분
    enum class EScenes
    {
        Intro,  // 0
        Start,  // 1
        END
    };

    // 목록 - 텍스트 색상 관리용(Windows 콘솔 색상 번호를 그대로 사용)
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
        END
    };

    // 목록 - 타자 효과 속도 고정값
    enum class ETypingSpeed
    {
        FAST = 10,
        SLOW = 100,
        END
    };

    //==========================================
    // 커서 표시 관련 함수
    //==========================================

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

    //==========================================
    // 텍스트 효과 함수
    //==========================================

    // 일정 시간 동안 대기 - 간격 애니메이션 효과
    inline void FnSleep(int _milliseconds)
    {
        // 시간 간격(duration) : 숫자값이 클수록 긴 시간, 작을수록 짧은 시간 간격
        this_thread::sleep_for(chrono::milliseconds(_milliseconds));
    }

    // 철자별 타이핑 효과 (문자열을 문자 단위로 출력하면서 지연)
    template <typename T>
    void FnApplyTypingEffectBySpelling(T _sentence, int _milliseconds)
    {
        for (const auto& ch : _sentence)
        {
            cout << ch;
            FnSleep(_milliseconds);
        }
    }

    // 줄별 타이핑 효과 (여러 줄의 문장을 한 줄씩 출력하며 지연)
    inline void FnApplyTypingEffectByLine(vector<string> _vec, int _milliseconds)
    {
        for (const string& sentence : _vec)
        {
            cout << sentence << endl;
            FnSleep(_milliseconds);
        }
    }

    //==========================================
    // 텍스트 색상 설정
    //==========================================

    // 텍스트 컬러 변경 (콘솔 텍스트 색상을 EColors 값에 따라 변경)
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

    // 텍스트 컬러 기본색 복구 (색상을 기본값(흰색)으로 복원)
    inline void FnSetTextDefault()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(EColors::WHITE));
    }

    //==========================================
    // 텍스트 효과 + 색상
    //==========================================

    // 철자별 타이핑 효과(입력된 스피드) + 색상
    inline void PrintBySpellingWithColor(string _str, EColors _color, ETypingSpeed _speed)
    {
        FnSetTextColor(_color);
        FnApplyTypingEffectBySpelling(_str, static_cast<int>(_speed));
        FnSetTextDefault();
    }

    // 줄별 타이핑 효과(입력된 스피드) + 색상
    inline void PrintByLineWithColor(vector<string> _vec, EColors _color, ETypingSpeed _speed)
    {
        FnSetTextColor(_color);
        FnApplyTypingEffectByLine(_vec, static_cast<int>(_speed));
        FnSetTextDefault();
    }

    //==========================================
    // 입력 유효성 검사
    // Input Validation
    //========================================== 
    // 문자열 입력값으로 정수 판별 확인 (정규식을 사용해 문자열이 숫자인지 판별)
    inline bool FnIsNumber(const std::string& s)
    {
        std::regex pattern("^-?\\d+(\\.\\d+)?$"); // 부호 있는 정수 또는 실수
        return std::regex_match(s, pattern);
    }
}

using namespace COMMON;
