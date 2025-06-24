#include "RandomUtil.h"

mt19937 RandomUtil::gen;

// �õ� �ʱ�ȭ
void RandomUtil::Init()
{
	random_device rd;
	gen.seed(rd());
}

// ���� ���� ����
int RandomUtil::GetRandomInt(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

// string format ��� ����
string RandomUtil::fillSides(const string& s, int width, char fillChar)
{
	int totalFill = width - s.size();
	if (totalFill <= 0) return s;

	int left = totalFill / 2;
	int right = totalFill - left;
	return string(left, fillChar) + s + string(right, fillChar);
}
