#pragma once
#include <iostream>
#include <istream>
#include <iomanip>  // setw, setfill 등
#include <regex>    // 정규표현식

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

#include <iomanip>  //setw

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

    // ANSI 컬러 코드 정의
#define RESET       "\033[0m"
#define RED_BG      "\033[41m \033[0m"
#define GREEN_BG    "\033[42m \033[0m"
#define BLACK_BG    "\033[40m \033[0m"

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

    //==========================================
    // 전투 장면 HP 바 표시 함수
    //==========================================

    // Windows 콘솔에서 ANSI 이스케이프 시퀀스(컬러, 텍스트 효과 등) 를 활성화
    inline void EnableANSIColors()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;

        // 현재 모드 가져오기
        if (!GetConsoleMode(hOut, &dwMode))
            return;

        // ANSI escape 시퀀스 활성화
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }

    // 플레이어와 적의 HP 바를 문자열로 반환, hp: 현재 HP, maxHp: 최대 HP, barWidth: 바의 너비
    inline string FnGetHealthBar(int _hp, int _maxHp, int _barWidth = 15)
    {
        string bar = "";

        // 현재 HP가 전체 체력에서 차지하는 비율을 계산, 바의 너비에 맞춰 상태를 계산
        int status = (_hp * _barWidth) / _maxHp;

        // 체력이 1 이상일 경우 최소 1칸 보장 (단, 체력이 0이면 0)
        if (_hp > 0 && status == 0)
        {
            status = 1;
        }

        // (Way 1) HP 표시 방식 : '|'
        for (int i = 0; i < _barWidth; ++i)
        {
            bar += (i < status) ? '|' : ' ';
        };

        //// (Way 2) HP 표시 방식 : 배경색
        //for (int i = 0; i < _barWidth; ++i)
        //{
        //    if (i < status)
        //    {
        //        //bar += GREEN_BG;  // GREEN 배경 (체력 있음)
        //        bar += RED_BG;  // RED 배경 (체력 있음)
        //    }
        //    else
        //    {
        //        bar += BLACK_BG;  // 검정색 배경 (체력 없음)
        //    }
        //}

        return bar;
    }

    // 플레이어와 적의 HP 상태 표시
    inline void FnPrintHpStatusBar(int _playerHp, int _playerMaxHp, int _enemyHp, int _enemyMaxHp, const string& _playerName, const string& _enemyName, int _space = 35)
    {
        const int consoleWidth = 90;
        // (Way 2) HP 표시 방식 : 배경색, 적용하는 경우 필요함.
        //EnableANSIColors();

        // 플레이어 상태 표시
        //cout << playerName << " HP: " << getHealthBar(playerHp, playerMaxHp) << " " << playerHp << "/" << playerMaxHp;
        string strPlayerStatus;
        strPlayerStatus += "HP:[";
        FnSetTextColor(EColors::YELLOW); cout << strPlayerStatus;

        // (Way 1) HP 표시 방식 : '|'
        strPlayerStatus.clear();
        strPlayerStatus += FnGetHealthBar(_playerHp, _playerMaxHp);   // 플레이어의 HP 바
        FnSetTextColor(EColors::GREEN); cout << strPlayerStatus;

        // (Way 2) HP 표시 방식 : 배경색
        //strPlayerStatus.clear();
        //strPlayerStatus += FnGetHealthBar(_playerHp, _playerMaxHp);   // 플레이어의 HP 바
        //cout << strPlayerStatus;

        strPlayerStatus.clear();
        strPlayerStatus += "] ";
        FnSetTextColor(EColors::YELLOW); cout << strPlayerStatus;
        strPlayerStatus.clear();
        strPlayerStatus += to_string(_playerHp);                     // 플레이어의 현재 HP
        FnSetTextColor(EColors::GREEN); cout << strPlayerStatus;
        strPlayerStatus.clear();
        strPlayerStatus += "/";
        strPlayerStatus += to_string(_playerMaxHp);                  // 플레이어의 최대 HP
        FnSetTextColor(EColors::YELLOW); cout << strPlayerStatus;

        //// 수정중
        // 여백 조정
        int spaceValue = 0;
        const int MAX_SIZE_NAME = 7; // ex) string BOSS_NAME = "BossMonster"; // 11글자
        //spaceValue = (MAX_SIZE_NAME <= _enemyName.size()) ? (25 - _playerName.length()) : (35 - _playerName.length());
        spaceValue = consoleWidth - 1
            - 22 - to_string(_enemyHp).size() - to_string(_enemyMaxHp).size()
            - 22 - _enemyName.size() - to_string(_playerHp).size() - to_string(_playerMaxHp).size();
        cout << string(spaceValue, ' ');

        // 적 상태 표시
        //cout << enemyName << " HP: " << getHealthBar(enemyHp, enemyMaxHp) << " " << enemyHp << "/" << enemyMaxHp << "\n";
        string strEnemyStatus;
        strEnemyStatus += _enemyName;
        FnSetTextColor(EColors::YELLOW); cout << strEnemyStatus;
        strEnemyStatus.clear();
        strEnemyStatus += " HP:[";
        FnSetTextColor(EColors::YELLOW); cout << strEnemyStatus;

        // (Way 1) HP 표시 방식 : '|'
        strEnemyStatus.clear();
        strEnemyStatus += FnGetHealthBar(_enemyHp, _enemyMaxHp);  // 적의 HP 바
        FnSetTextColor(EColors::RED); cout << strEnemyStatus;


        // (Way 2) HP 표시 방식 : 배경색
        //strEnemyStatus.clear();
        //strEnemyStatus += FnGetHealthBar(_enemyHp, _enemyMaxHp);  // 적의 HP 바
        //cout << strEnemyStatus;

        strEnemyStatus.clear();
        strEnemyStatus += "] ";
        FnSetTextColor(EColors::YELLOW); cout << strEnemyStatus;
        strEnemyStatus.clear();
        strEnemyStatus += to_string(_enemyHp);                   // 적의 현재 HP
        FnSetTextColor(EColors::RED); cout << strEnemyStatus;
        strEnemyStatus.clear();
        strEnemyStatus += "/";
        strEnemyStatus += to_string(_enemyMaxHp);                // 적의 최대 HP
        FnSetTextColor(EColors::YELLOW); cout << strEnemyStatus;

        // 줄바꿈
        cout << endl;
    }
}

using namespace COMMON;
