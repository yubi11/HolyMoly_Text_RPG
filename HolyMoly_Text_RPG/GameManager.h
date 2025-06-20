#pragma once
#ifndef	GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <algorithm>

#include "Monster.h"
#include "Character.h"
#include "Shop.h"


using namespace std;

class GameManager {
private:
	int level;
	Character* player;

public:
	GameManager() {}
	void createPlayer();
	void StartGame();
	Monster* generateMonster(int level);
	BossMonster* generateBossMonster(int level);
	void battle(Character* player);
	void visitShop(Character* player);
	void displayInventory(Character* player);
};



#endif