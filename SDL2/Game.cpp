#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Input.h"
#include <iostream>
#include "Map.h"
#include <chrono>

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
	text = gltCreateText();
}

void Game::destroy() {
	Window::destroy();
	renderer->destroy();
	SDL_Quit();
}

void Game::run()
{
	std::chrono::duration<double> elapsed_seconds;
	//logging
	GLint maxVertexComponents;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexComponents);
	std::cout << "max vertex uniform components : " << std::to_string(maxVertexComponents).c_str();

	int nDraws = 0;
	
	Quad* tq = &renderer->quads->tileQuad;

	glm::vec2 playerPosition = { 0, 3 };
	float drawDistance = 48;

	while (state.running)
	{
		auto start = std::chrono::steady_clock::now();
		Input::pollEvents(); // polls events and updates the input state
		Input::resolveCallBacks(); // call all registred callbacks and executes based on the input state


		//********************************
		//************DRAWING*************
		//********************************

		//CLEAR CANVAS
		renderer->clear();


		glm::vec2 startCoord = playerPosition - drawDistance;
		glm::vec2 EndCoord = playerPosition + drawDistance; 
		std::vector<glm::vec2> positionsOfQuadsToDraw;

		for (int i = (int)startCoord.x; i < (int)EndCoord.x; i++)
		{
			for (int j = (int)startCoord.y; j < (int)EndCoord.y; j++)
			{
				if (i != playerPosition.x || j != playerPosition.y)
				{
					positionsOfQuadsToDraw.push_back(glm::vec2{ i,j });
				}
			}
		}

		//DRAW START
		
		renderer->drawQuadInstanced(tq, positionsOfQuadsToDraw, { 1.0,1.0,0.0,1.0 }, positionsOfQuadsToDraw.size());

		//TEXT
		gltSetText
		(
			text, 
			(std::string("frame time : ") + 
			 std::to_string(elapsed_seconds.count()) +
			 std::string("s")
			).c_str()
		);
		renderer->drawText(text, glm::vec2(0, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0, true);

		//SWAP THE CANVAS
		renderer->Swap();
		auto end = std::chrono::steady_clock::now();
		elapsed_seconds = end - start;
	}

	gltDeleteText(text);
}

