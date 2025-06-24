#include "GameManager.h"
#include "ConsoleUI.h"


void StartGame(GameManager& gm)
{
	// 시드 초기화
	RandomUtil::Init();

	// 시작 화면
	ConsoleUI::title();

	// 플레이어 이름 받기
	ConsoleUI::getPlayerName();
	string playerName = gm.getPlayerName();

	// 플레이어 직업 받기
	vector<string> job =
	{
		"1. 전사",
		"2. 탱커",
		"3. 상인"
	};
	ConsoleUI::getPlayerJob(job);
	int playerJob = gm.getPlayerJob(job);

	// 직업, 이름 출력
	FnSetTextColor(EColors::YELLOW);
	cout << setfill(' ') << setw(ConsoleUI::consoleWidth) << right << job[playerJob - 1].substr(job[playerJob - 1].find(" ") + 1) + ", " + playerName << endl;
	FnSetTextDefault();

	gm.createPlayer(playerName, playerJob);

	Character* gamePlayer = gm.getPlayer();
	int level = gamePlayer->getLevel();

	while (level < 10)
	{

		// 새로운 몬스터
		gm.generateMonster(level);
		Monster* monster = gm.getMonster();

		monster->displayMonster();
		gm.battle();
		gm.addBattleLog();
		ConsoleUI::displayBattleResult(gm.getIsPlayerDead(), gamePlayer->getName(), monster->getName(), level);

		// 플레이어 사망 확인
		if (gm.getIsPlayerDead())
		{
			break;
		}

		// 경험치++ 레벨 업
		gm.addPlayerExperience();
		level = gamePlayer->getLevel();
		gm.setLevel(level);

		// 몬스터별 골드 획득 
		gm.addPlayerGold(monster->dropGold());

		// 몬스터 아이템 드랍
		// 수정 고려사항) 0~3번 랜덤하게 반복하도록
		int randCount = RandomUtil::GetRandomInt(0, 3);
		for (int i = 0; i < randCount; i++) 
		{
			Item* item = monster->dropItem();
			if (item != nullptr)
			{
				gamePlayer->addItem(item);
				cout << monster->getName() << "에게 " << item->getName() << "을(를) 얻었습니다." << endl;
			}
		}
		

		// 상점 방문
		gm.visitShop();
	}



	// 보스 몬스터
	if (!gm.getIsPlayerDead() && level == 10)
	{
		gm.generateBossMonster(level);
		Monster* monster = gm.getMonster();

		monster->displayMonster();
		gm.battle();
		gm.addBattleLog();
		ConsoleUI::displayBattleResult(gm.getIsPlayerDead(), gamePlayer->getName(), monster->getName(), level);
	}

	// 게임 종료 ui 출력
	if (gm.getIsPlayerDead()) 
	{
		ConsoleUI::gameOver();
	}
	else 
	{
		ConsoleUI::gameClear();
	}
	// 플레이 로그 출력
	//gm.displayPlayLog();
	ConsoleUI::displayPlayLog(
		gm.getPlayLog(), gm.getMonsterCount(), gamePlayer->getLevel(), gamePlayer->getGold());


}