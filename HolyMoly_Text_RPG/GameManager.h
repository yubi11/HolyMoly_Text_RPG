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
	int level = 1;						// 시작 레벨
	const int eventProbability = 25;	// 배틀 중 아이템 사용 확률
	const int experience = 50;			// 경험치 증가율 레벨 올라갈수록 줄어들게
	Character* player;					// 플레이어 캐릭터
	bool isPlayerDead = false;			// 플레이어 사망여부
	unique_ptr<Monster> monster;		// 몬스터 포인터
	int monsterCount = 0;				// 잡은 몬스터 수
	vector<string> playLog;				// 플레이 기록


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