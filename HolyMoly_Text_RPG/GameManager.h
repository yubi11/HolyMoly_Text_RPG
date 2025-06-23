#pragma once
#ifndef	GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <map> 
#include <memory>

#include "RandomUtil.h"
#include "Goblin.h"
#include "Troll.h"
#include "Orc.h"
#include "BossMonster.h"
#include "Character.h"
#include "Shop.h"

using namespace std;

class GameManager
{
private:
	int level = 1;						// ���� ����
	const int eventProbability = 10;	// ��Ʋ �� ������ ��� Ȯ��
	const int experience = 50;			// ����ġ ������
	Character* player;					// �÷��̾� ĳ����
	bool isPlayerDead = false;			// �÷��̾� �������
	unique_ptr<Monster> monster;		// ���� ������
	int monsterCount = 0;				// ���� ���� ��
	vector<string> playLog;				// �÷��� ���


public:

	void createPlayer();
	//void StartGame();
	void generateMonster(int level);
	void generateBossMonster(int level);
	void battle();
	void addPlayerExperience();
	void addPlayLog(string& log);
	void visitShop();
	void addPlayerGold(int gold);

	void displayInventory();
	void displayBattleResult();
	void displayPlayLog();

	//Getter
	int getLevel();
	int getExperience();
	Character* getPlayer();
	Monster* getMonster();
	bool getIsPlayerDead();
	int getMonsterCount();
	vector<string>& getPlayLog();
};



#endif