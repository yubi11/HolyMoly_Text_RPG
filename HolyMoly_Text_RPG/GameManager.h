#pragma once
#ifndef	GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <map> 
#include <memory>
#include <iomanip>

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
	const int eventProbability = 25;	// ��Ʋ �� ������ ��� Ȯ��
	const int experience = 50;			// ����ġ ������ ���� �ö󰥼��� �پ���
	Character* player;					// �÷��̾� ĳ����
	bool isPlayerDead = false;			// �÷��̾� �������
	unique_ptr<Monster> monster;		// ���� ������
	int monsterCount = 0;				// ���� ���� ��
	vector<string> playLog;				// �÷��� ���


public:

	void createPlayer(string name, int job);
	//void StartGame();
	void generateMonster(int level);
	void generateBossMonster(int level);
	void battle();
	void addPlayerExperience();
	void visitShop();
	void addPlayerGold(int gold);
	void addBattleLog();

	void displayInventory();
	void displayPlayLog();
	string getPlayerName();
	int getPlayerJob();

	//Getter
	int getLevel();
	int getExperience();
	Character* getPlayer();
	Monster* getMonster();
	bool getIsPlayerDead();
	int getMonsterCount();
	vector<string>& getPlayLog();

	//Setter
	void setLevel(int level);

};



#endif