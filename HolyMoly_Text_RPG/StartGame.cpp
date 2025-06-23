#include "GameManager.h"

void StartGame(GameManager& gm)
{
	// 시드 초기화
	RandomUtil::Init();


	// 화면 지우고 시작
	system("cls");
	gm.createPlayer();
	
	Character* gamePlayer = gm.getPlayer();
	int level = gamePlayer->getLevel();

	while (level < 10)
	{

		// 새로운 몬스터
		gm.generateMonster(level);
		Monster* monster = gm.getMonster();

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
		gm.addPlayerGold(randGold);

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

	// 플레이 로그 출력
	gm.displayPlayLog();

}