#include "Shop.h"
#include "gameEngine\Configs.h"
#include "utils\logs\Logs.h"
#include "utils\checkers\Checker.h"

Shop* Shop::instance = nullptr;

Shop::Shop(){
	// the costs information
	costs = new std::map<GameMemory::TowerSelected, unsigned int>();
	(*costs)[GameMemory::SAMPLE] = Configs::SAMPLE_TOWER_PRICE;
	(*costs)[GameMemory::INTELLIGENT] = Configs::INTELLIGENT_TOWER_PRICE;

	Checker::assertTrue((*costs)[GameMemory::SAMPLE] > 0, "Unknown sample tower cost.");
	Checker::assertTrue((*costs)[GameMemory::INTELLIGENT] > 0, "Unknown intelligent tower cost.");
}

Shop* Shop::getInstance() {
	if (instance == nullptr)
		instance = new Shop();
	return instance;
}

void Shop::providePlayer(Player* player, GameMemory::TowerSelected killer) {
	if (killer == GameMemory::SAMPLE)
		player->incMoney(Configs::ASTEROID_KILLED_BY_SAMPLED_GAIN);
	if (killer == GameMemory::INTELLIGENT)
		player->incMoney(Configs::ASTEROID_KILLED_BY_INTELLIGENT_GAIN);

	Logs::print("Updated player money: ", true, false);
	Logs::printG(player->getCurrentMoney());
	Logs::println(" dollars.", false, true);

}

// Gives the client a tower if it can, return false otherwise
bool Shop::buyTower(GameMemory::TowerSelected towerType, Player* client) const {
	if (towerType == GameMemory::UNKNOWN) {
		Logs::println("You don't know what to buy ?");
		return false;
	}

	Checker::assertNotNull(client, "Client unknown !");
	unsigned int clientMoney = client->getCurrentMoney();

	// check the client money
	if (clientMoney <= 0) {
		Logs::print("Player does not have enough money to buy a ", true, false);
		Logs::printG(towerType);
		Logs::println(".", false, true);
		return false;
	}

	// get the tower price
	unsigned int towerPrice = costs->find(towerType)->second;
	Checker::assertTrue(towerPrice > 0, "Tower price unknown !");
	int diff = clientMoney - towerPrice;

	// pre-calculate the player money
	if (diff < 0)
		return false;

	// get a tower
	client->incTowerCount(towerType);
	// pay for it
	client->decMoney(towerPrice);

	Logs::print("Client bought 1 ", true, false);
	Logs::printG(towerType);
	Logs::print(" for ", false, false);
	Logs::printG(towerPrice);
	Logs::print(" dollars, money left: ", false, false);
	Logs::printG(client->getCurrentMoney());
	Logs::println(".", false, true);
	return true;
}

bool Shop::buySampleTower(Player* client) const {
	Checker::assertNotNull(client, "Client unknown !");
	return buyTower(GameMemory::SAMPLE, client);
}

bool Shop::buyIntelligentTower(Player* client) const {
	Checker::assertNotNull(client, "Client unknown !");
	return buyTower(GameMemory::INTELLIGENT, client);
}