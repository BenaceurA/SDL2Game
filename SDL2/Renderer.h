#pragma once
#include <glad/glad.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include "Quad.h"
#include "GLBufferManager.h"
#include "ShaderProgram.h"

class Renderer
{
public:
	static void init();
	static void destroy();
	static void setClearColor(float r, float g , float b , float a);
	static void clear();
	static void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);
	static void Swap();
	static ShaderProgram* activeShader; //temporary
private:	
	static Quad quad;
	static void drawArrays(GLsizei n);	
	static SDL_GLContext GLContext;
	static GLBufferManager* bufferManager;

};

