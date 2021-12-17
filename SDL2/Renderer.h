#pragma once
#include <glad/glad.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include "Quad.h"
#include "GLBufferManager.h"
#include "ShaderProgram.h"

class Renderer
{
	struct quadPool
	{
		Quad tileQuad{ 1.0f,1.0f };
		Quad bigQuad{ 1.0f,2.0f };
	};

public:

	quadPool* quads;
	static Renderer* createInstance();
	static Renderer* getInstance();
	void init();
	void destroy();
	void setClearColor(float r, float g , float b , float a);
	void clear();
	void drawQuad(const Quad* quad,glm::vec2 position, glm::vec4 color);
	void Swap();
	ShaderProgram* activeShader; //temporary

private:
	static Renderer* renderer;	
	void drawArrays(GLsizei n);	
	SDL_GLContext GLContext;

};

