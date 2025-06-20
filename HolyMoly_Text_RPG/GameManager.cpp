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
	cout << "이름을 입력하세요: ";
	getline(cin, name);
	// character 클래스에 setName같은 public 함수 필요
	player = Character::getInstance();
	player->setName(name);
}

void GameManager::StartGame() {


}