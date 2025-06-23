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

