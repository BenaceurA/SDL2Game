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
		
		//testing : we assume the quad being drawn will be at position 0,0
		
		//get screenX and screenY of the quad being drawn
		//by getting the world position then multiply by view and proj and devide by W

		//Default positions of the quad
		glm::vec2 positions[4];
		positions[0] = {0.0f,0.0f};							//bottom left
		positions[1] = {tq->getWidth(),0.0f};				//bottom right
		positions[2] = {tq->getWidth(),tq->getHeight()};	//top right
		positions[3] = {0.0f,tq->getWidth()};				//top left

		//for each default position of the quad we will calculate it's screen coords
		glm::vec4 screenPos[4];
		for (size_t i = 0; i < 4; i++)
		{
			screenPos[i] = renderer->getCamera()->getProjection() * renderer->getCamera()->getView() * glm::vec4(positions[i], 0.0, 1.0);
			screenPos[i] /= screenPos[i].w;
		}

		//draw the quad	
		//only draw the quad if at least 1 screenPos.x is less then 1 and bigger than -1
		//OR at least 1 screenPos.y is less then 1 and bigget than -1

		bool xAxisHidden = true;
		bool yAxisHidden = true;
		for (size_t i = 0; i < 4; i++)
		{
			if (screenPos[i].x > -1.0f && screenPos[i].x < 1.0f)
			{
				xAxisHidden = false;
				break;
			}
		}
		for (size_t i = 0; i < 4; i++)
		{
			if (screenPos[i].y > -1.0f && screenPos[i].y < 1.0f)
			{
				yAxisHidden = false;
				break;
			}
		}
		if (!xAxisHidden && !yAxisHidden)
		{
			renderer->drawQuad(tq, { 0.0f,0.0f }, { 1.0,0.0,0.0,1.0 });
			gltSetText(text,std::string("DRAWING").c_str());
			renderer->drawText(text, glm::vec2(0, 80), glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0, true);
		}

		//draw the text
		for (size_t i = 0; i < 4; i++)
		{
			gltSetText(text, (std::to_string(screenPos[i].x) + std::string(",") + std::to_string(screenPos[i].y)).c_str());
			renderer->drawText(text, glm::vec2(0, 20*i), glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0, true);
		}
		
		//SWAP THE CANVAS
		renderer->Swap();
	}

	gltDeleteText(text);
}

