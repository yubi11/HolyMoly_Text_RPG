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
//get monsterCount
int GameManager::getMonsterCount() 
{
	return monsterCount;
}
//get playLog
vector<string>& GameManager::getPlayLog() 
{
	return playLog;
}
//set level
void GameManager::setLevel(int level) 
{
	this->level = level;
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

// 배틀 결과 로그에 추가
// 잡은 몬스터 카운트
void GameManager::addBattleLog() {
	if (isPlayerDead)
	{
		string log = player->getName() + "이(가) 레벨 "
			+ to_string(level) + " " + monster->getName() + "에게 쓰러졌습니다.";
		playLog.push_back(log);
	}
	else
	{
		string log = player->getName() + "이(가) 레벨 "
			+ to_string(level) + " " + monster->getName() + "을(를) 처치했습니다.";
		playLog.push_back(log);
		monsterCount++;
	}
}

// player와 monster 배틀
void GameManager::battle()
{
	string playerName = player->getName();
	string monsterName = monster->getName();
	int consoleWidth = 90;

	cout << RandomUtil::fillSides("레벨 " + to_string(level), consoleWidth, '=') << endl;
	cout << RandomUtil::fillSides("야생의 " + monsterName + "이(가) 나타났습니다!", consoleWidth, ' ') << endl << endl;
	FnSetTextColor(EColors::CYAN);
	cout << RandomUtil::fillSides("체력: " + to_string(monster->getHealth()) + " 공격력: "+to_string(monster->getAttack()), consoleWidth, ' ') << endl << endl;
	FnSetTextDefault();

	while (1)
	{
		string battleLog;
		//플레이어가 몬스터 공격
		monster->takeDamage(player->getAttack());

		// 공격 메시지
		battleLog = playerName + "이(가) " + monsterName + "을(를) 공격합니다!";
		cout << battleLog << endl;

		// 받은 피해 메시지
		FnSetTextColor(EColors::LIGHT_CYAN);
		battleLog = monsterName + "이(가) " + to_string(player->getAttack()) + "의 피해를 입었습니다. "+monsterName + "의 체력: " + to_string(monster->getHealth());
		cout << setfill(' ') << setw(consoleWidth) << right << battleLog << endl << endl;
		FnSetTextDefault();

		// 몬스터 생존 여부 확인
		if (monster->getHealth() <= 0)
		{
			isPlayerDead = false;
			break;
		}
		FnSetTextColor(EColors::DARK_GRAY);
		cout << RandomUtil::fillSides("", consoleWidth, '-') << endl << endl;
		FnSetTextDefault();
		FnSleep(300);

		//몬스터가 플레이어 공격
		player->takeDamage(monster->getAttack());

		// 공격 메시지
		string skill = monster->getSkill();
		FnSetTextColor(EColors::LIGHT_CYAN);
		battleLog = monsterName + "의 ";
		cout << setfill(' ') << setw(consoleWidth - skill.length() - 3) << right << battleLog;
		FnSetTextColor(EColors::LIGHT_RED);
		cout << setfill(' ') << right << skill;
		FnSetTextColor(EColors::LIGHT_CYAN);
		cout << setfill(' ') << right << "!!!" << endl;
		FnSetTextDefault();

		// 받은 피해 메시지
		battleLog = playerName + "이(가) " + to_string(monster->getAttack()) + "의 피해를 입었습니다. " + playerName + "의 체력: " + to_string(player->getHealth());
		cout << battleLog << endl << endl;
		
		// 플레이어 생존 여부 확인
		if (player->getHealth() <= 0)
		{
			isPlayerDead = true;
			break;
		}

		FnSetTextColor(EColors::DARK_GRAY);
		cout << RandomUtil::fillSides("", consoleWidth, '-') << endl << endl;
		FnSetTextDefault();
		FnSleep(300);

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
// 플레이어 골드 추가
void GameManager::addPlayerGold(int gold)
{
	player->setGold(player->getGold() + gold);
}
// 상점 방문
void GameManager::visitShop()
{
	string answer = "";
	cout << endl << "상점에 방문하시겠습니까? (Y/N) : ";

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
		// 수정: Shop shop(player, bool) 10%확률로 true
		int randomInt = RandomUtil::GetRandomInt(1, 100);
		bool isTrue = false;
		if (randomInt <= 20 )
		{
			isTrue = true;
		}
		Shop gameShop(player, isTrue);
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

// 플레이어 이름 받아오기
string GameManager::getPlayerName() 
{
	string name;
	getline(cin, name);
	while (name == "")
	{
		cout << "이름을 입력하세요: ";
		getline(cin, name);
	}
	return name;
}
// 플레이어 직업 받아오기
int GameManager::getPlayerJob()
{
	string str;
	getline(cin, str);

	while (!FnIsNumber(str))
	{
		cout << "알맞은 번호를 입력하세요: ";
		getline(cin, str);
	}

	return stoi(str);
}
// 플레이어 생성
void GameManager::createPlayer(string name, int job)
{	
	this->player = Character::getInstance(name, job);
}
