#include "GameManager.h"
#include <iostream>


Monster* GameManager::generateMonster(int level) {

}
BossMonster* GameManager::generateBossMonster(int level) {

}
void GameManager::battle(Character* player) {


}
void GameManager::visitShop(Character* player) {


}
void GameManager::displayInventory(Character* player) {


}
void GameManager::createPlayer() {
	string name;
	cout << "�̸��� �Է��ϼ���: ";
	getline(cin, name);
	// character Ŭ������ setName���� public �Լ� �ʿ�
	player = Character::getInstance();
	player->setName(name);
}

void GameManager::StartGame() {


}