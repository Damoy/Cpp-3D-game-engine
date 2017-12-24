#include "gameEngine\GameEngine.h"

// The main entry point
int main(void) {

	{
		GameEngine game;
		game.start();
	}

	std::cin.get();
	return 0;
}