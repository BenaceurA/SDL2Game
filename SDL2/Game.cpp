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
	text = gltCreateText();
}

void Game::destroy() {
	Window::destroy();
	renderer->destroy();
	SDL_Quit();
}

void Game::run()
{
	//logging
	GLint maxVertexComponents;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexComponents);
	std::cout << "max vertex uniform components : " << std::to_string(maxVertexComponents).c_str();

	//create a map
	const int mapWidth = 64;
	const int mapHeight = 64;
	Map map(mapWidth, mapHeight);
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
		
		int nDraws = 0;
		std::vector<glm::vec2> positionsOfQuadsToDraw;
		//loop the map and get all the visible tile positions
		for (float i = 0; i < mapWidth * tq->getWidth(); i+=tq->getWidth())
		{
			for (float j = 0; j < mapHeight * tq->getHeight(); j+=tq->getHeight())
			{
				//get world vertex positions
				glm::vec2 pos[4];
				pos[0] = { i,j };
				pos[1] = { i+tq->getWidth(),j };
				pos[2] = { i+tq->getWidth(),j+tq->getHeight() };
				pos[3] = { i,j+tq->getWidth() };

				//tranform into screenPos
				glm::vec4 screenPos[4];
				for (size_t k = 0; k < 4; k++)
				{
					screenPos[k] = renderer->getCamera()->getProjection() * renderer->getCamera()->getView() * glm::vec4(pos[k], 0.0, 1.0);
					screenPos[k] /= screenPos[k].w;
				}

				//check the quad is hidden
				bool xAxisHidden = true;
				bool yAxisHidden = true;
				for (size_t l = 0; l < 4; l++)
				{
					if (screenPos[l].x > -1.0f && screenPos[l].x < 1.0f)
					{
						xAxisHidden = false;
					}
					if (screenPos[l].y > -1.0f && screenPos[l].y < 1.0f)
					{
						yAxisHidden = false;
					}
				}
				if (!xAxisHidden && !yAxisHidden)
				{
					positionsOfQuadsToDraw.push_back({ i,j });
					nDraws++;
				}
			}
		}
		renderer->drawQuadInstanced(tq, positionsOfQuadsToDraw, { 1.0,1.0,0.0,1.0 }, positionsOfQuadsToDraw.size());

		//TEXT
		gltSetText(text, std::to_string(nDraws).c_str());
		renderer->drawText(text, glm::vec2(0, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0, true);

		//SWAP THE CANVAS
		renderer->Swap();
	}

	gltDeleteText(text);
}

