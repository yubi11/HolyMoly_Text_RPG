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

// level ������� ���� ���� ����
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
// level ������� ���� ���� ����
void GameManager::generateBossMonster(int level)
{
	monster = make_unique<BossMonster>(level);
}

// ��Ʋ ��� ���
void GameManager::displayBattleResult() {
	if (isPlayerDead)
	{
		cout << "���� ����. " << player->getName() << "��(��) �׾����ϴ�." << endl;
		string log = player->getName() + "��(��) ���� "
			+ to_string(level) + " " + monster->getName() + "���� ���������ϴ�.";
		addPlayLog(log);
	}
	else
	{
		cout << "�����մϴ�! " << monster->getName()
			<< "��(��) óġ�ϰ� ����" << level << "�� Ŭ�����߽��ϴ�." << endl;
		string log = player->getName() + "��(��) ���� "
			+ to_string(level) + " " + monster->getName() + "��(��) óġ�߽��ϴ�.";
		addPlayLog(log);
	}
}

// player�� monster ��Ʋ
void GameManager::battle()
{
	string playerName = player->getName();
	string monsterName = monster->getName();
	// ȭ�� �����
	system("cls");
	cout << "========���� " << level << "========" << endl;
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
		int randNum = RandomUtil::GetRandomInt(1, 100);	// ������ ��� Ȯ��

		map<string, pair<Item*, int>> playerInventory = player->getInventory();

		if (playerInventory.size() > 0 && randNum < eventProbability)
		{
			int randIdx = RandomUtil::GetRandomInt(0, playerInventory.size() - 1);	// ����� ������ �ε��� 
			player->useItem(next(playerInventory.begin(), randIdx)->first);
		}

	}

}
// �÷��̾� ����ġ �߰�
void GameManager::addPlayerExperience()
{
	player->addExperience(experience);
}
// �÷��� �α� �߰�
void GameManager::addPlayLog(string& log)
{
	playLog.push_back(log);
}
// �÷��̾� ��� �߰�
void GameManager::addPlayerGold(int gold)
{
	player->setGold(player->getGold() + gold);
}
// ���� �湮
void GameManager::visitShop()
{
	string answer = "";
	cout << "������ �湮�Ͻðڽ��ϱ�? (Y/N)";

	while (1)
	{
		getline(cin, answer);
		cin.ignore();
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
void GameManager::displayInventory()
{
	// player inventory map<string, pair<Item*,int>>�� ����
	map<string, pair<Item*, int>>& inventory = player->getInventory();
	for (auto p : inventory)
	{
		cout << p.first << " " << p.second.second << "��" << endl;
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
	cin.ignore();
	this->player = Character::getInstance(name);
}
