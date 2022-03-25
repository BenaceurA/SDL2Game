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

	glm::vec2 playerPosition = { 0, 0 };
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

		playerPosition = renderer->getCamera()->position;

		glm::vec2 startCoord = playerPosition - drawDistance;
		glm::vec2 EndCoord = playerPosition + drawDistance; 
		std::vector<glm::vec2> positionsOfGreenQuadsToDraw;
		std::vector<glm::vec2> positionsOfBlueQuadsToDraw;
		std::vector<glm::vec2> positionsOfGreyQuadsToDraw;
		for (int i = (int)startCoord.x; i < (int)EndCoord.x; i++)
		{
			for (int j = (int)startCoord.y; j < (int)EndCoord.y; j++)
			{
				double height = Map::getHeightAtLocation(i, j);

				if (height < 0.30f)
				{
					positionsOfBlueQuadsToDraw.push_back(glm::vec2{ i,j });
				}
				else if (height > 0.30f && height < 0.65f)
				{
					positionsOfGreenQuadsToDraw.push_back(glm::vec2{ i,j });
				}
				else if (height > 0.65f) {
					positionsOfGreyQuadsToDraw.push_back(glm::vec2{ i,j });
				}
			}
		}

		//DRAW START
		
		renderer->drawQuadInstanced(tq, positionsOfBlueQuadsToDraw, { 0.0,0.0,1.0,1.0 }, positionsOfBlueQuadsToDraw.size());
		renderer->drawQuadInstanced(tq, positionsOfGreenQuadsToDraw, { 0.0,1.0,0.0,1.0 }, positionsOfGreenQuadsToDraw.size());
		renderer->drawQuadInstanced(tq, positionsOfGreyQuadsToDraw, { 0.5,0.5,0.5,1.0 }, positionsOfGreyQuadsToDraw.size());
		renderer->drawQuad(tq,  playerPosition , { 1.0,1.0,1.0,1.0 });
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

		gltSetText
		(
			text,
			(std::string("player position : ") +
			 std::to_string(playerPosition.x) + " " + std::to_string(playerPosition.y)
			).c_str()
		);
		renderer->drawText(text, glm::vec2(0, 12), glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0, true);
		//SWAP THE CANVAS
		renderer->Swap();
		auto end = std::chrono::steady_clock::now();
		elapsed_seconds = end - start;
	}

	gltDeleteText(text);
}

