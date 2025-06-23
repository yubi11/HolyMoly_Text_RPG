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
	gm.createPlayer();
	
	Character* gamePlayer = gm.getPlayer();
	int level = gamePlayer->getLevel();

	while (level < 10)
	{

		// 새로운 몬스터
		gm.generateMonster(level);
		Monster* monster = gm.getMonster();

		monster->displayMonster();
		gm.battle();
		gm.displayBattleResult();

		// 플레이어 사망 확인
		if (gm.getIsPlayerDead())
		{
			break;
		}

		// 경험치++ 레벨 업
		gm.addPlayerExperience();
		level = gamePlayer->getLevel();

		// 골드 랜덤 획득
		// (수정 필요)몬스터별 골드 획득 
		int randGold = RandomUtil::GetRandomInt(5, 15);	// 랜덤한 양의 골드
		gm.addPlayerGold(monster->dropGold());

		// 몬스터 아이템 드랍
		Item* item = monster->dropItem();
		if (item != nullptr)
		{
			gamePlayer->addItem(item);
			cout << monster->getName() << "에게 " << item->getName() << "을(를) 얻었습니다." << endl;
		}

		// 상점 방문
		gm.visitShop();
	}



	// 보스 몬스터
	if (!gm.getIsPlayerDead() && level == 10)
	{
		gm.generateBossMonster(level);
		Monster* monster = gm.getMonster();

		gm.battle();
		gm.displayBattleResult();
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