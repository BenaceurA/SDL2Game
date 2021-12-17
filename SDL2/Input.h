#pragma once
#include <SDL_events.h>
#include "GameState.h"
#include <unordered_map>

enum class Key
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Z,
	S,
	Q,
	D,
	ESCAPE,
	LSHIFT,
	SIZE
};

enum class State
{
	KEYUP,
	KEYDOWN
};

class Input
{
	
public:
	static void pollEvents();	
	static bool isKeyPressed(const Key& k);
	static void init(GameState* gameState);
private:
	static GameState* gameState;
	static void handleEvent(const SDL_Event& e);
	static void handleKeyUpEvent(const SDL_Event& e);
	static void handleKeyDownEvent(const SDL_Event& e);
	static std::unordered_map<Key, State> keyState;
	static std::unordered_map<Key, SDL_KeyCode> rawKeyMap;
};
