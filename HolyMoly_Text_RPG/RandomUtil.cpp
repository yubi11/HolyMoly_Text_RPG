#include "RandomUtil.h"

mt19937 RandomUtil::gen;

// 시드 초기화
void RandomUtil::Init()
{
	random_device rd;
	gen.seed(rd());
}

// 랜덤 정수 생성
int RandomUtil::GetRandomInt(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

