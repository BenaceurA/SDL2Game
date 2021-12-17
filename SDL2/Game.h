#pragma once
#include "GameState.h"

class Game
{
public:
	static Game* createInstance();
	static Game* getInstance();
	void init();
	void run();
	void destroy();
private:
	static Game* game;
	GameState state;
};
