#include "StartGame.h"
#include <windows.h>

void StartGame(GameManager& gm)
{
	// 게임 타이틀
	system("title 홀리몰리 어드벤처");

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
		"2. 팔라딘",
		"3. 상인"
	};
	ConsoleUI::getPlayerJob(job);
	int playerJob = gm.getPlayerJob();

	// 직업, 이름 출력
	string playerDetail;
	if (playerJob > job.size() || playerJob <= 0)
	{
		playerDetail = "가지지 못한 자";
	}
	else
	{
		playerDetail = job[playerJob - 1].substr(job[playerJob - 1].find(" ") + 1);
	}
	playerDetail += ", " + playerName;
	FnSetTextColor(EColors::YELLOW);
	cout << setfill(' ') << setw(ConsoleUI::consoleWidth) << right << playerDetail << endl;
	FnSetTextDefault();

	// 플레이어 인스턴스 받아오기
	gm.createPlayer(playerName, playerJob);

	Character* gamePlayer = gm.getPlayer();
	int level = gamePlayer->getLevel();

	// 플레이어 스탯 출력
	gamePlayer->displayStatus();

	ConsoleUI::pressEnter();

	// 배틀
	while (level < 10)
	{
		// 새로운 몬스터
		gm.generateMonster(level);
		Monster* monster = gm.getMonster();

		// 배틀 시작 전 씬 플레이
		ConsoleUI::playScene();

		// 배틀 시작
		system("cls");
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
		cout << monster->getName() << "에게 " << monster->dropGold() << " 골드를 얻었습니다." << endl;

		// 몬스터 아이템 드랍
		// 수정 고려사항) 0~3번 랜덤하게 반복하도록
		int randCount = RandomUtil::GetRandomInt(0, 3);
		for (int i = 0; i < randCount; i++)
		{
			Item* item = monster->dropItem();
			if (item != nullptr)
			{
				cout << monster->getName() << "에게 " << item->getName() << "을(를) 얻었습니다." << endl;
				gamePlayer->addItem(item);
			}
		}

		// 상점 방문
		gm.visitShop();
	}



	// 보스 몬스터
	if (!gm.getIsPlayerDead() && level >= 10)
	{
		gm.generateBossMonster(level);
		Monster* monster = gm.getMonster();
		// 배틀 시작 전 씬 플레이
		ConsoleUI::playScene();
		system("cls");
		monster->displayMonster();
		gm.battle();
		gm.addBattleLog();
		ConsoleUI::displayBattleResult(gm.getIsPlayerDead(), gamePlayer->getName(), monster->getName(), level);
	}

	// 사운드 적용상 추가. 순서 중요. 로그 출력 이후로 효과음 정지하기 위함.
	bool isClear = false;

	// 게임 종료 ui 출력
	if (gm.getIsPlayerDead())
	{
		ConsoleUI::pressEnter();
		ConsoleUI::gameOver();
	}
	else
	{
		ConsoleUI::pressEnter();
		ConsoleUI::gameClear();
		isClear = true;
	}
	// 플레이 로그 출력
	//gm.displayPlayLog();
	ConsoleUI::displayPlayLog(
		gm.getPlayLog(), gm.getMonsterCount(), gamePlayer->getLevel(), gamePlayer->getGold());

	if (isClear)
	{
		FnStopSFX_GameClear(); // 효과음 정지
	}
	else
	{
		FnStopSFX_GameOver(); // 효과음 정지
	}

}