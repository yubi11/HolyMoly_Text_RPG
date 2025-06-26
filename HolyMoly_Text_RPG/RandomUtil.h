#pragma once

#include <random>
#include <string>

using namespace std;

class RandomUtil {
private:
	static mt19937 gen;
public:
	static void Init();	//�õ� �ʱ�ȭ
	static int GetRandomInt(int min, int max);	//���� ���� ����
	static string fillSides(const string& s, int width, char fillChar = ' ');	// �ؽ�Ʈ ��� ���� �� ���� ä���
};
