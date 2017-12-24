#include "Player.h"
#include "gameEngine\Configs.h"
#include "utils\logs\Logs.h"

Player* Player::instance = nullptr;

Player::Player()
	: money(Configs::PLAYER_BASE_MONEY), totalTowerCount(0), asteroidsDestroyed(0){

	// the player camera is the main camera, already generated
	camera = &Configs::MAIN_CAMERA;
	towersCount = new std::map<GameMemory::TowerSelected, unsigned short>();
	(*towersCount)[GameMemory::SAMPLE] = 0;
	(*towersCount)[GameMemory::INTELLIGENT] = 0;

	Logs::print("Player initial money: ", true, false);
	Logs::printG(money);
	Logs::println(".", false, true);
}

Player::~Player(){
	delete towersCount;
	towersCount = nullptr;
}

Player* Player::getInstance() {
	if (instance == nullptr)
		instance = new Player();
	return instance;
}

void Player::incTowerCount(GameMemory::TowerSelected of) {
	std::map<GameMemory::TowerSelected, unsigned short>::iterator it = towersCount->find(of);
	if (it != towersCount->end()) {
		(*it).second++;
	}

	incTotalTowerCount();
}

void Player::decTowerCount(GameMemory::TowerSelected of) {
	std::map<GameMemory::TowerSelected, unsigned short>::iterator it = towersCount->find(of);
	if (it != towersCount->end()) {
		(*it).second--;
	}

	decTotalTowerCount();
}

int Player::incMoney(unsigned int of) {
	money += of;
	return money;
}

int Player::incMoney() {
	return incMoney(1);
}

int Player::decMoney(unsigned int of) {
	money -= of;
	if (money < 0)
		money = 0;
	return money;
}

int Player::decMoney() {
	return decMoney(1);
}

void Player::incAsteroidsDestroyed(unsigned int of) {
	asteroidsDestroyed += of;
}

void Player::incAsteroidsDestroyed() {
	incAsteroidsDestroyed(1);
}

void Player::incTotalTowerCount(unsigned short of) {
	totalTowerCount += of;
}

void Player::incTotalTowerCount() {
	incTotalTowerCount(1);
}

void Player::decTotalTowerCount(unsigned short of) {
	totalTowerCount -= of;
}

void Player::decTotalTowerCount() {
	decTotalTowerCount(1);
}

void Player::reset() {
	money = Configs::PLAYER_BASE_MONEY;
	totalTowerCount = 0;
	asteroidsDestroyed = 0;
	towersCount->clear();
	(*towersCount)[GameMemory::SAMPLE] = 0;
	(*towersCount)[GameMemory::INTELLIGENT] = 0;
}

Camera* Player::getCamera() const { return camera; }
int Player::getCurrentMoney() const { return money; }

unsigned short Player::getTotalTowerCount() const { return totalTowerCount; }
unsigned int Player::getAsteroidsDestroyedCount() const { return asteroidsDestroyed; }

unsigned short Player::getTowersCount(GameMemory::TowerSelected of) const {
	std::map<GameMemory::TowerSelected, unsigned short>::iterator it = towersCount->find(of);
	if (it != towersCount->end()) {
		return (*it).second;
	}
	return 0;
}
