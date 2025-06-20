#include "GameManager.h"
#include <iostream>


// level ������� ���� ���� ����
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
// level ������� ���� ���� ����
BossMonster* GameManager::generateBossMonster(int level) 
{
	return new BossMonster(level);
}

// ��Ʋ ��� ���
void GameManager::displayBattleResult(Character* player) {
	if (isPlayerDead) 
	{
		cout <<"���� ����. " << player->getName() << "��(��) �׾����ϴ�." << endl;
	}
	else 
	{
		cout << "�����մϴ�! " << monster->getName() 
			<< "��(��) óġ�ϰ� ����" << level << "�� Ŭ�����߽��ϴ�." << endl;
	}
}

// player�� monster ��Ʋ
void GameManager::battle(Character* player) 
{
	string playerName = player->getName();
	string monsterName = monster->getName();
	// ȭ�� �����
	system("cls");
	cout << "========���� "<<level<<"========" << endl;
	cout << "�߻��� " << monsterName << "��(��) ��Ÿ�����ϴ�!" << endl;

	while (1) 
	{
		//�÷��̾ ���� ����
		monster->takeDamage(player->getAttack());
		cout << playerName << "��(��) " << monsterName << "��(��) �����մϴ�! "
			<< monsterName << "ü��: " << monster->getHealth() << endl;
		if (monster->getHealth() <= 0)
		{
			isPlayerDead = false;
			break;
		}

		
		//���Ͱ� �÷��̾� ����
		player->takeDamage(monster->getAttack());
		cout << monsterName << "��(��) " << playerName << "��(��) �����մϴ�! "
			<< playerName << "ü��: " << player->getHealth() << endl;
		if (player->getHealth() <= 0) 
		{
			isPlayerDead = true;
			break;
		}

		// ������ ���� ��� 
		uniform_int_distribution<int> dist(1, 100);
		int randNum = dist(gen);	// ������ ��� Ȯ��

		map<string, int> playerInventory = player->getInventory();

		if (playerInventory.size() > 0 && randNum < eventProbability) 
		{
			uniform_int_distribution<int> dist(0, playerInventory.size() - 1);
			int randIdx = dist(gen);	// ����� ������ �ε��� 
			player->useItem(randIdx);
		}

	}

}

// ���� �湮
void GameManager::visitShop(Character* player) 
{
	string answer = "";
	cout << "������ �湮�Ͻðڽ��ϱ�? (Y/N)";
	
	while (1) 
	{
		getline(cin, answer);
		answer = toupper(answer[0]);
		if (answer != "Y" && answer != "N") 
		{
			cout << "Y�� N�� �Է��ϼ���: ";
		}
		else 
		{
			break;
		}
	}

	if (answer == "Y") 
	{
		// ȭ�� ����� ������ ǥ��
		system("cls");
		gameShop.OnEnter(player);

	}
	else if (answer == "N") 
	{
		cout << "������ �����ƽ��ϴ�." << endl;
	}
}

// �÷��̾� �κ��丮 ���
void GameManager::displayInventory(Character* player) 
{
	// player inventory map<string, int>�� ����
	map<string, int>& inventory = player->getInventory();
	for (auto p : inventory) 
	{
		cout << p.first << " " << p.second << "��" << endl;
	}
}

// �÷��� ���� ���
void GameManager::displayPlayLog() 
{
	//ȭ�� �����
	system("cls");

	int totalMonster = playLog.size();
	if (isPlayerDead) 
	{
		totalMonster--;
		cout << "���� ����" << endl;
	}
	else 
	{
		cout << "���� ����" << endl;
	}
	cout << "========�÷��� ���========" << endl;
	for (string s : playLog) 
	{
		cout << s << endl;
	}
	cout << "�� óġ�� ����: " << totalMonster << "���� / ���� ������ ����: " << level << endl;

}

// �÷��̾� ����
void GameManager::createPlayer() 
{
	string name = "";
	cout << "�̸��� �Է��ϼ���: ";
	getline(cin, name);
	this->gamePlayer = Character::getInstance(name);
}

// ���� �÷���
void GameManager::StartGame() 
{
	// ȭ�� ����� ����
	system("cls");
	createPlayer();

	string log = "";
	while (level < 10) 
	{
		// �α� �ʱ�ȭ
		log = "";
		// ���ο� ����
		monster = make_unique<Monster>(generateMonster(level));
		// �÷��� �α� �ۼ�
		log += gamePlayer->getName() + "��(��) ���� "
			+to_string(level) + " " + monster->getName();

		battle(gamePlayer);
		displayBattleResult(gamePlayer);

		// �÷��̾� ��� Ȯ��
		if (isPlayerDead)
		{	
			log += "���� ���������ϴ�.";
			playLog.push_back(log);
			break;
		}
		else 
		{
			log += "��(��) óġ�߽��ϴ�.";
			playLog.push_back(log);
		}

		// ����ġ++ ���� ��
		gamePlayer->addExperience(experience);
		if (gamePlayer->getExperience() >= 100) 
		{
			level++;
			gamePlayer->levelUp();
		}

		// ��� ���� ȹ��
		uniform_int_distribution<int> dist(5, 15);
		int randGold = dist(gen);	// ������ ���� ���
		gamePlayer->setGold(randGold);

		// ���� ������ ���
		Item* item = monster->dropItem();
		if (item != nullptr)
		{
			gamePlayer->addItem(*item);
			cout << monster->getName() << "���� " << item->getName() << "��(��) ������ϴ�." << endl;
		}

		// ���� �湮
		visitShop(gamePlayer);
	}



	// ���� ����
	if (!isPlayerDead && level == 10)
	{
		monster = make_unique<BossMonster>(generateBossMonster(level));
		log += gamePlayer->getName() + "��(��) ���� "
			+ to_string(level) + " " + monster->getName();

		battle(gamePlayer);
		displayBattleResult(gamePlayer);

		if (isPlayerDead) 
		{
			log += "���� ���������ϴ�.";
			playLog.push_back(log);
		}
		else 
		{
			log += "��(��) óġ�߽��ϴ�.";
			playLog.push_back(log);
		}
	}

	// �÷��� �α� ���
	displayPlayLog();
	
}