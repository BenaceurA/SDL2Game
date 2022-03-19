#include "Renderer.h"
#include <stdexcept>
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include "Exception.h"


Renderer* Renderer::renderer = nullptr;
Renderer* Renderer::createInstance()
{
	if (renderer != nullptr)
	{
		return nullptr;
	}
	renderer = new Renderer();
	return renderer;
}

Renderer* Renderer::getInstance() {
	return renderer;
}

void Renderer::init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	if (Window::window == nullptr)
		throw std::runtime_error("window was nullptr!");
	GLContext = SDL_GL_CreateContext(Window::window);
	if (GLContext == NULL)
		throw std::runtime_error("failed to create context!");

	//****LOAD OPENGL FUNCTIONS*****
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	initText();

	//Camera and Shader shouldn't be created here.
	activeCamera = new Camera{ {0.0f,0.0f},Window::resolution.x / Window::resolution.y,50.0f }; 
	activeShader = new ShaderProgram{ "shader.vert", "shader.frag" };

	activeShader->Use();
	activeShader->setMat4("projection", activeCamera->getProjection());

	quads = new QuadContainer();

	glViewport(0, 0, (int)Window::resolution.x, (int)Window::resolution.y);
}

void Renderer::initText() {
	gltInit();
}

void Renderer::destroy()
{
	delete activeCamera;
	delete activeShader;
	delete quads;
	gltTerminate();
	SDL_GL_DeleteContext(GLContext);
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

const ShaderProgram* Renderer::getShader()
{
	return activeShader;
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawQuad(const Quad* quad, glm::vec2 position, glm::vec4 color)
{ 
	activeShader->Use();
	quad->bind();
	activeShader->setVec4("color",color); //color
	glm::mat4 m(1);
	m = glm::translate(m, glm::vec3(position, 0.0));
	activeShader->setMat4("model",m); //position
	activeShader->setMat4("view", activeCamera->getView());
	drawElements(6);
	quad->unbind();
}

void Renderer::drawQuad(const Quad* quad, glm::vec2 position, Texture* texture)
{
	activeShader->Use();
	quad->bind();
	texture->bind(0);
	activeShader->setInt("texture01", 0);
	activeShader->setBool("hasTexture", true); //hasTexture
	glm::mat4 m(1);
	m = glm::translate(m, glm::vec3(position, 0.0));
	activeShader->setMat4("model", m); //position
	activeShader->setMat4("view", activeCamera->getView());
	drawElements(6);
	quad->unbind();
}

void Renderer::drawQuadInstanced(const Quad* quad, std::vector<glm::vec2> positions, glm::vec4 color, int instanceCount)
{
	activeShader->Use();
	quad->bind();
	//add per instance attribute to the quad here (position)
	quad->addInstancedAttribute(positions.data(), positions.size()*sizeof(float)*2);
	activeShader->setVec4("color", color);
	activeShader->setBool("isInstanced", true);	
	for (size_t i = 0; i < instanceCount; i++)
	{
		glm::mat4 m(1);
		m = glm::translate(m, glm::vec3(positions[i], 0.0));
		activeShader->setMat4("models[" + std::to_string(i) + "]", m);
	}
	activeShader->setMat4("view", activeCamera->getView());
	drawElementsInstanced(6, instanceCount);
	quad->unbind();
}

//this creates GLText every time u call it, prefer using the other version and pass in GLText
void Renderer::drawText(const char* text, glm::vec2 position, glm::vec4 color, float scale,bool screenCoord)
{
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLTtext* Text = gltCreateText();
	gltSetText(Text, text);
	// Begin text drawing (this for instance calls glUseProgram)
	gltBeginDraw();

	// Draw any amount of text between begin and end
	gltColor(color.r, color.g, color.b, color.a);
	if (screenCoord)
	{
		gltDrawText2D(Text, position.x, position.y, scale);
	}
	else {
		gltDrawText2D(Text, (position.x + 1) * 0.5f * Window::resolution.x, (-position.y + 1) * 0.5f * Window::resolution.y, scale);
	}
	
	// Finish drawing text
	gltEndDraw();
	gltDeleteText(Text);
}

void Renderer::drawText(GLTtext* text, glm::vec2 position, glm::vec4 color, float scale, bool screenCoord)
{
	//GLTtext shouldn't be created every frame

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Begin text drawing (this for instance calls glUseProgram)
	gltBeginDraw();

	// Draw any amount of text between begin and end
	gltColor(color.r, color.g, color.b, color.a);
	if (screenCoord)
	{
		gltDrawText2D(text, position.x, position.y, scale);
	}
	else {
		gltDrawText2D(text, (position.x + 1) * 0.5f * Window::resolution.x, (-position.y + 1) * 0.5f * Window::resolution.y, scale);
	}

	// Finish drawing text
	gltEndDraw();
}

void Renderer::Swap()
{
	SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
}

void Renderer::drawElements(GLsizei count)
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void Renderer::drawElementsInstanced(GLsizei count, GLsizei instancecount)
{
	glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0, instancecount);
}

void Renderer::setCamera(Camera* camera)
{
	this->activeCamera = camera;
}

Camera* Renderer::getCamera()
{
	return this->activeCamera;
}
