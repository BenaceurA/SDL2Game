#include "Input.h"

std::unordered_map<Key, State> Input::keyState;
std::unordered_map<Key, SDL_KeyCode> Input::rawKeyMap;
GameState* Input::gameState = nullptr;

void Input::init(GameState* gameState)
{
	Input::gameState = gameState;

	rawKeyMap[Key::LEFT] = SDLK_LEFT;
	rawKeyMap[Key::UP] = SDLK_UP;
	rawKeyMap[Key::RIGHT] = SDLK_RIGHT;
	rawKeyMap[Key::DOWN] = SDLK_DOWN;
	rawKeyMap[Key::D] = SDLK_d;
	rawKeyMap[Key::Z] = SDLK_z;
	rawKeyMap[Key::Q] = SDLK_q;
	rawKeyMap[Key::Z] = SDLK_z;
	rawKeyMap[Key::ESCAPE] = SDLK_ESCAPE;
	rawKeyMap[Key::LSHIFT] = SDLK_LSHIFT;
}

void Input::pollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		handleEvent(e);
	}
}

bool Input::isKeyPressed(const Key& k)
{
	return (keyState[k] == State::KEYDOWN ? true : false);
}

void Input::handleEvent(const SDL_Event& e)
{	
	if (e.type == SDL_QUIT)
	{
		gameState->running = false;
	}
	else if (e.type == SDL_KEYUP) handleKeyUpEvent(e);
	else if (e.type == SDL_KEYDOWN) handleKeyDownEvent(e);
}

void Input::handleKeyUpEvent(const SDL_Event& e)
{	
	for (auto k : rawKeyMap)
	{
		if (e.key.keysym.sym == k.second)
		{
			keyState[k.first] = State::KEYUP;
			break;
		}		
	}
}

void Input::handleKeyDownEvent(const SDL_Event& e)
{
	for (auto k : rawKeyMap)
	{
		if (e.key.keysym.sym == k.second)
		{
			keyState[k.first] = State::KEYDOWN;
			break;
		}
	}
}
