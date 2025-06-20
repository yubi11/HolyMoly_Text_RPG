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
	int level = 1;						// 시작 레벨
	const int eventProbability = 10;	// 배틀 중 아이템 사용 확률
	const int experience = 50;			// 경험치 증가율
	Character* gamePlayer;				// 플레이어 캐릭터
	bool isPlayerDead = false;			// 플레이어 사망여부
	Shop gameShop;				// 상점
	unique_ptr<Monster> monster;		// 몬스터 포인터
	vector<string> playLog;				// 플레이 기록
	
	// 난수 생성기 초기화
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