#pragma once
#include <string>
using namespace std;

class Character;

class Item
{
public:
	virtual ~Item() {}
	virtual string getName() const = 0;             	// ������ �̸�
	virtual int getPrice() const = 0;               	// ������ ����
	virtual int getItemValue() const = 0;       	// ȿ�� ��ġ (ȸ����, ���ݷ� ��)
	virtual void use(Character* character) = 0; // ĳ���Ϳ��� ������ ���
	virtual void display() const = 0;			// ������ ���� �ֿܼ� ���
};