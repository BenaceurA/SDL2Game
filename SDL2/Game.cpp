#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Input.h"
#include <iostream>
#include "Map.h"

Game* Game::game = nullptr;

Game* Game::createInstance()
{
	if (game != nullptr)
	{
		return nullptr;
	}
	game = new Game();
	return game;
}

Game* Game::getInstance()
{
	return game;
}

void Game::init() {
	renderer = Renderer::createInstance();
	Window::init({1600,800}); // 1600 by 600 resolution window
	renderer->init();
	Input::init(&state);
	renderer->setClearColor(0.f, 0.f, 0.f, 1.f);
}

void Game::destroy() {
	Window::destroy();
	renderer->destroy();
	SDL_Quit();
}

void Game::run()
{
	//TEXT TESTING
	GLTtext* text = gltCreateText();

	Map map(24, 24);
	map.generateHeightMap();
	while (state.running)
	{
		Input::pollEvents(); // polls events and updates the input state
		Input::resolveCallBacks(); // call all registred callbacks and executes based on the input state


		//********************************
		//************DRAWING*************
		//********************************

		//CLEAR CANVAS
		renderer->clear();


		Quad* tq = &renderer->quads->tileQuad;
		Quad* bq = &renderer->quads->bigQuad;

		//DRAW START
		int DrawCount = 0;

		gltSetText(text,std::to_string(DrawCount).c_str());
		renderer->drawText(text, glm::vec2(0, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0, true);
		
		//SWAP THE CANVAS
		renderer->Swap();
	}

	gltDeleteText(text);
}
