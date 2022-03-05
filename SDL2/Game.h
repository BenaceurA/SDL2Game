#pragma once
#include "GameState.h"
#include "Renderer.h"


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
	Renderer* renderer;
	GameState state;
};
