#pragma once
#include <SDL.h>
#include <glm/glm.hpp>

class Window
{
public:
	static void init(glm::vec2 resolution);
	static void destroy();
	static SDL_Window* window;
	static glm::vec2 resolution;
private:
	
};

