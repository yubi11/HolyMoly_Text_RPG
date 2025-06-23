#pragma once
#include <random>

using namespace std;

class RandomUtil {
private:
	static mt19937 gen;
public:
	static void Init();	//시드 초기화
	static int GetRandomInt(int min, int max);	//랜덤 정수 생성
};