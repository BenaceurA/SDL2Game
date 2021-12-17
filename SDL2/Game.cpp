#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Input.h"

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
	Window::init({1600,600}); // 1600 by 600 resolution window
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
	//set a camera
	Camera camera{ {0.0f,0.0f},Window::resolution.x / Window::resolution.y,1.0f };
	//set a shader before doing draw calls
	ShaderProgram shader("shader.vert", "shader.frag");
	shader.Use();
	
	shader.setMat4("projection", camera.getProjection());

	renderer->activeShader = &shader; //give renderer the ability to change uniforms
	while (state.running)
	{
		Input::pollEvents();

		if (Input::isKeyPressed(Key::LSHIFT))
		{
			if (Input::isKeyPressed(Key::UP))
				camera.setZoom(camera.getZoom() + 0.1f);

			if (Input::isKeyPressed(Key::DOWN))
				camera.setZoom(camera.getZoom() - 0.1f);
		}
		else {
			if (Input::isKeyPressed(Key::ESCAPE))
				state.running = false;

			if (Input::isKeyPressed(Key::RIGHT))
				camera.position.x += 0.05f;

			if (Input::isKeyPressed(Key::LEFT))
				camera.position.x -= 0.05f;

			if (Input::isKeyPressed(Key::UP))
				camera.position.y += 0.05f;

			if (Input::isKeyPressed(Key::DOWN))
				camera.position.y -= 0.05f;
		}
		
		shader.setMat4("view", camera.getView());

		//********************************
		//************DRAWING*************
		//********************************

		//CLEAR CANVAS
		renderer->clear();
		
		Quad* tq = &renderer->quads->tileQuad;
		Quad* bq = &renderer->quads->bigQuad;

		//DRAW START
		for (size_t i = 0; i <= 10; i++)
		{
			for (size_t j = 0; j <= 10; j++)
			{
				renderer->drawQuad(tq,glm::vec2(i,j), glm::vec4(0.1f, 0.9f, 0.f, 1.f));
			}
		}
		renderer->drawQuad(bq, glm::vec2(camera.position.x, camera.position.y), glm::vec4(1.f, 1.0f,1.f, 1.f));
		//DRAW END

		//SWAP THE CANVAS
		renderer->Swap();
	}
}
