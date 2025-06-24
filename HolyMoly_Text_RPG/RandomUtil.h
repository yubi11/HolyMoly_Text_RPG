#pragma once

#include <random>
#include <string>

using namespace std;

class RandomUtil {
private:
	static mt19937 gen;
public:
	static void Init();	//시드 초기화
	static int GetRandomInt(int min, int max);	//랜덤 정수 생성
	static string fillSides(const string& s, int width, char fillChar = ' ');	// 텍스트 가운데 정렬 및 문자 채우기
};
