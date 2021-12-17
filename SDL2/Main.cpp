#include <iostream>
#include "Game.h"

int main(int argc, char* args[]) try {
	Game* game = Game::createInstance();

	if (game == nullptr)
	{
		return 1;
	}

	game->init();
	game->run();
	game->destroy();
	return 0;
}
catch (std::exception& e) {
	std::cout << "runtime error : " << e.what();
	return 1;
}