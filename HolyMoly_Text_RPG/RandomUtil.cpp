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

// string format 가운데 정렬
string RandomUtil::fillSides(const string& s, int width, char fillChar)
{
	int totalFill = width - s.size();
	if (totalFill <= 0) return s;

	int left = totalFill / 2;
	int right = totalFill - left;
	return string(left, fillChar) + s + string(right, fillChar);
}
