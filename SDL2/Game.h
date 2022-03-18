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
	Renderer* renderer; //used to render to the window using opengl
	GLTtext* text; //used to setup a text for rendering
	GameState state; //holds some garbage
};
