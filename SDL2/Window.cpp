#include "Window.h"
#include <stdexcept>

SDL_Window* Window::window = nullptr;
glm::vec2 Window::resolution;

void Window::init(glm::vec2 resolution)
{
	Window::resolution = resolution;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("gfg", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)resolution.x, (int)resolution.y, SDL_WINDOW_OPENGL);	
}

void Window::destroy()
{
	SDL_DestroyWindow(window);
}
