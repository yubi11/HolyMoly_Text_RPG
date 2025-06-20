#include "GameManager.h"
#include <iostream>


// level 기반으로 랜덤 몬스터 생성
Monster* GameManager::generateMonster(int level) 
{
	uniform_int_distribution<int> dist(0, 2);
	int randNum = dist(gen);

	switch (randNum) 
	{
	case 0:
		return new Goblin(level);
		break;
	case 1:
		return new Orc(level);
		break;
	case 2:
		return new Troll(level);
		break;
	}
}
// level 기반으로 보스 몬스터 생성
BossMonster* GameManager::generateBossMonster(int level) 
{
	return new BossMonster(level);
}

// 배틀 결과 출력
void GameManager::displayBattleResult(Character* player) {
	if (isPlayerDead) 
	{
		cout <<"게임 오버. " << player->getName() << "이(가) 죽었습니다." << endl;
	}
	else 
	{
		cout << "축하합니다! " << monster->getName() 
			<< "을(를) 처치하고 레벨" << level << "을 클리어했습니다." << endl;
	}
}

// player와 monster 배틀
void GameManager::battle(Character* player) 
{
	string playerName = player->getName();
	string monsterName = monster->getName();
	// 화면 지우기
	system("cls");
	cout << "========레벨 "<<level<<"========" << endl;
	cout << "야생의 " << monsterName << "이(가) 나타났습니다!" << endl;

	while (1) 
	{
		//플레이어가 몬스터 공격
		monster->takeDamage(player->getAttack());
		cout << playerName << "이(가) " << monsterName << "을(를) 공격합니다! "
			<< monsterName << "체력: " << monster->getHealth() << endl;
		if (monster->getHealth() <= 0)
		{
			isPlayerDead = false;
			break;
		}

		
		//몬스터가 플레이어 공격
		player->takeDamage(monster->getAttack());
		cout << monsterName << "이(가) " << playerName << "을(를) 공격합니다! "
			<< playerName << "체력: " << player->getHealth() << endl;
		if (player->getHealth() <= 0) 
		{
			isPlayerDead = true;
			break;
		}

		// 아이템 랜덤 사용 
		uniform_int_distribution<int> dist(1, 100);
		int randNum = dist(gen);	// 아이템 사용 확률

		map<string, int> playerInventory = player->getInventory();

		if (playerInventory.size() > 0 && randNum < eventProbability) 
		{
			uniform_int_distribution<int> dist(0, playerInventory.size() - 1);
			int randIdx = dist(gen);	// 사용할 아이템 인덱스 
			player->useItem(randIdx);
		}

	}

}

// 상점 방문
void GameManager::visitShop(Character* player) 
{
	string answer = "";
	cout << "상점에 방문하시겠습니까? (Y/N)";
	
	while (1) 
	{
		getline(cin, answer);
		answer = toupper(answer[0]);
		if (answer != "Y" && answer != "N") 
		{
			cout << "Y나 N을 입력하세요: ";
		}
		else 
		{
			break;
		}
	}

	if (answer == "Y") 
	{
		// 화면 지우고 상점만 표시
		system("cls");
		gameShop.OnEnter(player);

	}
	else if (answer == "N") 
	{
		cout << "상점을 지나쳤습니다." << endl;
	}
}

// 플레이어 인벤토리 출력
void GameManager::displayInventory(Character* player) 
{
	// player inventory map<string, int>로 변경
	map<string, int>& inventory = player->getInventory();
	for (auto p : inventory) 
	{
		cout << p.first << " " << p.second << "개" << endl;
	}
}

// 플레이 내역 출력
void GameManager::displayPlayLog() 
{
	//화면 지우기
	system("cls");

	int totalMonster = playLog.size();
	if (isPlayerDead) 
	{
		totalMonster--;
		cout << "게임 오버" << endl;
	}
	else 
	{
		cout << "게임 성공" << endl;
	}
	cout << "========플레이 기록========" << endl;
	for (string s : playLog) 
	{
		cout << s << endl;
	}
	cout << "총 처치한 몬스터: " << totalMonster << "마리 / 최종 도달한 레벨: " << level << endl;

}

// 플레이어 생성
void GameManager::createPlayer() 
{
	string name = "";
	cout << "이름을 입력하세요: ";
	getline(cin, name);
	this->gamePlayer = Character::getInstance(name);
}

// 게임 플레이
void GameManager::StartGame() 
{
	// 화면 지우고 시작
	system("cls");
	createPlayer();

	string log = "";
	while (level < 10) 
	{
		// 로그 초기화
		log = "";
		// 새로운 몬스터
		monster = make_unique<Monster>(generateMonster(level));
		// 플레이 로그 작성
		log += gamePlayer->getName() + "이(가) 레벨 "
			+to_string(level) + " " + monster->getName();

		battle(gamePlayer);
		displayBattleResult(gamePlayer);

		// 플레이어 사망 확인
		if (isPlayerDead)
		{	
			log += "에게 쓰러졌습니다.";
			playLog.push_back(log);
			break;
		}
		else 
		{
			log += "을(를) 처치했습니다.";
			playLog.push_back(log);
		}

		// 경험치++ 레벨 업
		gamePlayer->addExperience(experience);
		if (gamePlayer->getExperience() >= 100) 
		{
			level++;
			gamePlayer->levelUp();
		}

		// 골드 랜덤 획득
		uniform_int_distribution<int> dist(5, 15);
		int randGold = dist(gen);	// 랜덤한 양의 골드
		gamePlayer->setGold(randGold);

		// 몬스터 아이템 드랍
		Item* item = monster->dropItem();
		if (item != nullptr)
		{
			gamePlayer->addItem(*item);
			cout << monster->getName() << "에게 " << item->getName() << "을(를) 얻었습니다." << endl;
		}

		// 상점 방문
		visitShop(gamePlayer);
	}



	// 보스 몬스터
	if (!isPlayerDead && level == 10)
	{
		monster = make_unique<BossMonster>(generateBossMonster(level));
		log += gamePlayer->getName() + "이(가) 레벨 "
			+ to_string(level) + " " + monster->getName();

		battle(gamePlayer);
		displayBattleResult(gamePlayer);

		if (isPlayerDead) 
		{
			log += "에게 쓰러졌습니다.";
			playLog.push_back(log);
		}
		else 
		{
			log += "을(를) 처치했습니다.";
			playLog.push_back(log);
		}
	}

	// 플레이 로그 출력
	displayPlayLog();
	
}