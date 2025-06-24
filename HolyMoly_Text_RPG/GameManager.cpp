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

// ��Ʋ ��� �α׿� �߰�
// ���� ���� ī��Ʈ
void GameManager::addBattleLog() {
	if (isPlayerDead)
	{
		string log = player->getName() + "��(��) ���� "
			+ to_string(level) + " " + monster->getName() + "���� ���������ϴ�.";
		playLog.push_back(log);
	}
	else
	{
		string log = player->getName() + "��(��) ���� "
			+ to_string(level) + " " + monster->getName() + "��(��) óġ�߽��ϴ�.";
		playLog.push_back(log);
		monsterCount++;
	}
}

// player�� monster ��Ʋ
void GameManager::battle()
{
	string playerName = player->getName();
	string monsterName = monster->getName();
	int consoleWidth = 90;

	cout << RandomUtil::fillSides("���� " + to_string(level), consoleWidth, '=') << endl;
	cout << RandomUtil::fillSides("�߻��� " + monsterName + "��(��) ��Ÿ�����ϴ�!", consoleWidth, ' ') << endl << endl;
	FnSetTextColor(EColors::CYAN);
	cout << RandomUtil::fillSides("ü��: " + to_string(monster->getHealth()) + " ���ݷ�: "+to_string(monster->getAttack()), consoleWidth, ' ') << endl << endl;
	FnSetTextDefault();

	while (1)
	{
		string battleLog;
		//�÷��̾ ���� ����
		monster->takeDamage(player->getAttack());

		// ���� �޽���
		battleLog = playerName + "��(��) " + monsterName + "��(��) �����մϴ�!";
		cout << battleLog << endl;

		// ���� ���� �޽���
		FnSetTextColor(EColors::LIGHT_CYAN);
		battleLog = monsterName + "��(��) " + to_string(player->getAttack()) + "�� ���ظ� �Ծ����ϴ�. "+monsterName + "�� ü��: " + to_string(monster->getHealth());
		cout << setfill(' ') << setw(consoleWidth) << right << battleLog << endl << endl;
		FnSetTextDefault();

		// ���� ���� ���� Ȯ��
		if (monster->getHealth() <= 0)
		{
			isPlayerDead = false;
			break;
		}
		FnSetTextColor(EColors::DARK_GRAY);
		cout << RandomUtil::fillSides("", consoleWidth, '-') << endl << endl;
		FnSetTextDefault();
		FnSleep(300);

		//���Ͱ� �÷��̾� ����
		player->takeDamage(monster->getAttack());

		// ���� �޽���
		string skill = monster->getSkill();
		FnSetTextColor(EColors::LIGHT_CYAN);
		battleLog = monsterName + "�� ";
		cout << setfill(' ') << setw(consoleWidth - skill.length() - 3) << right << battleLog;
		FnSetTextColor(EColors::LIGHT_RED);
		cout << setfill(' ') << right << skill;
		FnSetTextColor(EColors::LIGHT_CYAN);
		cout << setfill(' ') << right << "!!!" << endl;
		FnSetTextDefault();

		// ���� ���� �޽���
		battleLog = playerName + "��(��) " + to_string(monster->getAttack()) + "�� ���ظ� �Ծ����ϴ�. " + playerName + "�� ü��: " + to_string(player->getHealth());
		cout << battleLog << endl << endl;
		
		// �÷��̾� ���� ���� Ȯ��
		if (player->getHealth() <= 0)
		{
			isPlayerDead = true;
			break;
		}

		FnSetTextColor(EColors::DARK_GRAY);
		cout << RandomUtil::fillSides("", consoleWidth, '-') << endl << endl;
		FnSetTextDefault();
		FnSleep(300);

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
// �÷��̾� ��� �߰�
void GameManager::addPlayerGold(int gold)
{
	player->setGold(player->getGold() + gold);
}
// ���� �湮
void GameManager::visitShop()
{
	string answer = "";
	cout << endl << "������ �湮�Ͻðڽ��ϱ�? (Y/N) : ";

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
		// ����: Shop shop(player, bool) 10%Ȯ���� true
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

// �÷��̾� �̸� �޾ƿ���
string GameManager::getPlayerName() 
{
	string name;
	getline(cin, name);
	while (name == "")
	{
		cout << "�̸��� �Է��ϼ���: ";
		getline(cin, name);
	}
	return name;
}
// �÷��̾� ���� �޾ƿ���
int GameManager::getPlayerJob()
{
	string str;
	getline(cin, str);

	while (!FnIsNumber(str))
	{
		cout << "�˸��� ��ȣ�� �Է��ϼ���: ";
		getline(cin, str);
	}

	return stoi(str);
}
// �÷��̾� ����
void GameManager::createPlayer(string name, int job)
{	
	this->player = Character::getInstance(name, job);
}
