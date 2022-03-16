#pragma once
#include <glad/glad.h>
#define GLT_IMPLEMENTATION
#include "gltext.h"
#include <SDL.h>
#include <glm/glm.hpp>
#include "Quad.h"
#include "GLBufferManager.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Texture.h"

class Renderer
{
	struct QuadContainer
	{
		Quad tileQuad{ 1.0f,1.0f };
		Quad bigQuad{ 2.0f,2.0f };
	};

public:

	static Renderer* createInstance();
	static Renderer* getInstance();
	void init();
	void destroy();
	void setClearColor(float r, float g , float b , float a);
	const ShaderProgram* getShader();
	void clear();
	void drawQuad(const Quad* quad, glm::vec2 position, glm::vec4 color);
	void drawQuad(const Quad* quad, glm::vec2 position, Texture* texture);
	void drawQuadInstanced(const Quad* quad, std::vector<glm::vec2> positions, glm::vec4 color, int instanceCount);
	void drawText(const char* text, glm::vec2 position, glm::vec4 color ,float scale, bool screenCoord);
	void drawText(GLTtext* text, glm::vec2 position, glm::vec4 color, float scale, bool screenCoord);
	void Swap();
	void setCamera(Camera* camera);
	Camera* getCamera();
	QuadContainer* quads;

private:
	static Renderer* renderer;
	Camera* activeCamera;
	ShaderProgram* activeShader;
	void drawElements(GLsizei n);
	void drawElementsInstanced(GLsizei count, GLsizei instancecount);
	void initText();
	SDL_GLContext GLContext;

};

