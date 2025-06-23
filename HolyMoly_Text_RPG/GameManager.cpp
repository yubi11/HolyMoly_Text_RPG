#include "GameManager.h"
#include <iostream>


//get level
int GameManager::getLevel()
{
	return level;
}
//get experience
int GameManager::getExperience()
{
	return experience;
}
//get player
Character* GameManager::getPlayer()
{
	return player;
}
//get monster
Monster* GameManager::getMonster()
{
	return monster.get();
}
//get isPlayerDead
bool GameManager::getIsPlayerDead()
{
	return isPlayerDead;
}

// level 기반으로 랜덤 몬스터 생성
void GameManager::generateMonster(int level)
{
	int randNum = RandomUtil::GetRandomInt(0, 2);

	switch (randNum)
	{
	case 0:
		monster = make_unique<Goblin>(level);
		break;
	case 1:
		monster = make_unique<Orc>(level);
		break;
	case 2:
		monster = make_unique<Troll>(level);
		break;
	default:
		monster = nullptr;
		break;
	}
}
// level 기반으로 보스 몬스터 생성
void GameManager::generateBossMonster(int level)
{
	monster = make_unique<BossMonster>(level);
}

// 배틀 결과 출력
void GameManager::displayBattleResult() {
	if (isPlayerDead)
	{
		cout << "게임 오버. " << player->getName() << "이(가) 죽었습니다." << endl;
		string log = player->getName() + "이(가) 레벨 "
			+ to_string(level) + " " + monster->getName() + "에게 쓰러졌습니다.";
		addPlayLog(log);
	}
	else
	{
		cout << "축하합니다! " << monster->getName()
			<< "을(를) 처치하고 레벨" << level << "을 클리어했습니다." << endl;
		string log = player->getName() + "이(가) 레벨 "
			+ to_string(level) + " " + monster->getName() + "을(를) 처치했습니다.";
		addPlayLog(log);
	}
}

// player와 monster 배틀
void GameManager::battle()
{
	string playerName = player->getName();
	string monsterName = monster->getName();
	// 화면 지우기
	system("cls");
	cout << "========레벨 " << level << "========" << endl;
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
		int randNum = RandomUtil::GetRandomInt(1, 100);	// 아이템 사용 확률

		map<string, pair<Item*, int>> playerInventory = player->getInventory();

		if (playerInventory.size() > 0 && randNum < eventProbability)
		{
			int randIdx = RandomUtil::GetRandomInt(0, playerInventory.size() - 1);	// 사용할 아이템 인덱스 
			player->useItem(next(playerInventory.begin(), randIdx)->first);
		}

	}

}
// 플레이어 경험치 추가
void GameManager::addPlayerExperience()
{
	player->addExperience(experience);
}
// 플레이 로그 추가
void GameManager::addPlayLog(string& log)
{
	playLog.push_back(log);
}
// 플레이어 골드 추가
void GameManager::addPlayerGold(int gold)
{
	player->setGold(player->getGold() + gold);
}
// 상점 방문
void GameManager::visitShop()
{
	string answer = "";
	cout << "상점에 방문하시겠습니까? (Y/N)";

	while (1)
	{
		getline(cin, answer);
		cin.ignore();
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
void GameManager::displayInventory()
{
	// player inventory map<string, pair<Item*,int>>로 변경
	map<string, pair<Item*, int>>& inventory = player->getInventory();
	for (auto p : inventory)
	{
		cout << p.first << " " << p.second.second << "개" << endl;
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
	cin.ignore();
	this->player = Character::getInstance(name);
}
