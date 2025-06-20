#pragma once
#ifndef	GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <map> 
#include <memory>
#include <random>


#include "Monster.h"
#include "Character.h"
#include "Shop.h"

using namespace std;

class GameManager 
{
private:
	int level = 1;						// ���� ����
	const int eventProbability = 10;	// ��Ʋ �� ������ ��� Ȯ��
	const int experience = 50;			// ����ġ ������
	Character* gamePlayer;				// �÷��̾� ĳ����
	bool isPlayerDead = false;			// �÷��̾� �������
	Shop gameShop;				// ����
	unique_ptr<Monster> monster;		// ���� ������
	vector<string> playLog;				// �÷��� ���
	
	// ���� ������ �ʱ�ȭ
	mt19937 gen;

public:
	GameManager() : gen(random_device{}()) {}
	void createPlayer();
	void StartGame();
	Monster* generateMonster(int level);
	BossMonster* generateBossMonster(int level);
	void battle(Character* player);
	void visitShop(Character* player);
	void displayInventory(Character* player);
	void displayBattleResult(Character* player);
	void displayPlayLog();
};



#endif