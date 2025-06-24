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
	string playerName = gm.getPlayerName();

	// �÷��̾� ���� �ޱ�
	vector<string> job =
	{
		"1. ����",
		"2. ��Ŀ",
		"3. ����"
	};
	ConsoleUI::getPlayerJob(job);
	int playerJob = gm.getPlayerJob(job);

	// ����, �̸� ���
	FnSetTextColor(EColors::YELLOW);
	cout << setfill(' ') << setw(ConsoleUI::consoleWidth) << right << job[playerJob - 1].substr(job[playerJob - 1].find(" ") + 1) + ", " + playerName << endl;
	FnSetTextDefault();

	gm.createPlayer(playerName, playerJob);

	Character* gamePlayer = gm.getPlayer();
	int level = gamePlayer->getLevel();

	while (level < 10)
	{

		// ���ο� ����
		gm.generateMonster(level);
		Monster* monster = gm.getMonster();

		monster->displayMonster();
		gm.battle();
		gm.addBattleLog();
		ConsoleUI::displayBattleResult(gm.getIsPlayerDead(), gamePlayer->getName(), monster->getName(), level);

		// �÷��̾� ��� Ȯ��
		if (gm.getIsPlayerDead())
		{
			break;
		}

		// ����ġ++ ���� ��
		gm.addPlayerExperience();
		level = gamePlayer->getLevel();
		gm.setLevel(level);

		// ���ͺ� ��� ȹ�� 
		gm.addPlayerGold(monster->dropGold());

		// ���� ������ ���
		// ���� �������) 0~3�� �����ϰ� �ݺ��ϵ���
		int randCount = RandomUtil::GetRandomInt(0, 3);
		for (int i = 0; i < randCount; i++) 
		{
			Item* item = monster->dropItem();
			if (item != nullptr)
			{
				gamePlayer->addItem(item);
				cout << monster->getName() << "���� " << item->getName() << "��(��) ������ϴ�." << endl;
			}
		}
		

		// ���� �湮
		gm.visitShop();
	}



	// ���� ����
	if (!gm.getIsPlayerDead() && level == 10)
	{
		gm.generateBossMonster(level);
		Monster* monster = gm.getMonster();

		monster->displayMonster();
		gm.battle();
		gm.addBattleLog();
		ConsoleUI::displayBattleResult(gm.getIsPlayerDead(), gamePlayer->getName(), monster->getName(), level);
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