#pragma once
#include <random>

using namespace std;

class RandomUtil {
private:
	static mt19937 gen;
public:
	static void Init();	//�õ� �ʱ�ȭ
	static int GetRandomInt(int min, int max);	//���� ���� ����
};