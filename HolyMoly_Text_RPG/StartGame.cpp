#include "GameManager.h"
#include "ConsoleUI.h"


void StartGame(GameManager& gm)
{
	// �õ� �ʱ�ȭ
	RandomUtil::Init();

	// ���� ȭ��
	ConsoleUI::title();

	// �÷��̾� �̸� �ޱ�
	ConsoleUI::getPlayerName();
	gm.createPlayer();
	
	Character* gamePlayer = gm.getPlayer();
	int level = gamePlayer->getLevel();

	while (level < 10)
	{

		// ���ο� ����
		gm.generateMonster(level);
		Monster* monster = gm.getMonster();

		monster->displayMonster();
		gm.battle();
		gm.displayBattleResult();

		// �÷��̾� ��� Ȯ��
		if (gm.getIsPlayerDead())
		{
			break;
		}

		// ����ġ++ ���� ��
		gm.addPlayerExperience();
		level = gamePlayer->getLevel();

		// ��� ���� ȹ��
		// (���� �ʿ�)���ͺ� ��� ȹ�� 
		int randGold = RandomUtil::GetRandomInt(5, 15);	// ������ ���� ���
		gm.addPlayerGold(monster->dropGold());

		// ���� ������ ���
		Item* item = monster->dropItem();
		if (item != nullptr)
		{
			gamePlayer->addItem(item);
			cout << monster->getName() << "���� " << item->getName() << "��(��) ������ϴ�." << endl;
		}

		// ���� �湮
		gm.visitShop();
	}



	// ���� ����
	if (!gm.getIsPlayerDead() && level == 10)
	{
		gm.generateBossMonster(level);
		Monster* monster = gm.getMonster();

		gm.battle();
		gm.displayBattleResult();
	}

	// ���� ���� ui ���
	if (gm.getIsPlayerDead()) 
	{
		ConsoleUI::gameOver();
	}
	else 
	{
		ConsoleUI::gameClear();
	}
	// �÷��� �α� ���
	//gm.displayPlayLog();
	ConsoleUI::displayPlayLog(
		gm.getPlayLog(), gm.getMonsterCount(), gamePlayer->getLevel(), gamePlayer->getGold());


}