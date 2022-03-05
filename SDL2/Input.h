#pragma once
#include <SDL_events.h>
#include <glm/glm.hpp>
#include "GameState.h"
#include <unordered_map>
#include <functional>

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
	static glm::vec2 getMousePosition();
	static void init(GameState* gameState);
	static void resolveCallBacks();
	static void registerCallBack(std::function<void()> callback);
private:
	static GameState* gameState;
	static void handleEvent(const SDL_Event& e);
	static void handleKeyUpEvent(const SDL_Event& e);
	static void handleKeyDownEvent(const SDL_Event& e);
	static std::unordered_map<Key, State> keyState;
	static std::unordered_map<Key, SDL_KeyCode> rawKeyMap;
	static std::unordered_map<Key, std::string> actionKeyMap;
	static std::vector<std::function<void()>> callbacks;
};
