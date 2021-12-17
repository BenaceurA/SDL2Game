#include "Renderer.h"
#include <stdexcept>
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
SDL_GLContext Renderer::GLContext = nullptr;
GLBufferManager* Renderer::bufferManager = nullptr;
ShaderProgram* Renderer::activeShader = nullptr;

void Renderer::init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	if (Window::window == nullptr)
	{
		throw std::runtime_error("window was nullptr!");
	}
	GLContext = SDL_GL_CreateContext(Window::window);
	if (GLContext == NULL)
	{
		throw std::runtime_error("failed to create context!");
	}
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	bufferManager = new GLBufferManager();
	glViewport(0, 0, (int)Window::resolution.x, (int)Window::resolution.y);
}

void Renderer::destroy()
{
	delete bufferManager;
	SDL_GL_DeleteContext(GLContext);
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawQuad(glm::vec2 position,glm::vec2 size, glm::vec4 color)
{ 
	//u set the position and color in the shader before drawing
	activeShader->setVec4("color",color); //color
	glm::mat4 m(1);
	m = glm::translate(m, glm::vec3(position, 0.0));
	activeShader->setMat4("model",m); //position
	drawArrays(6);
}

void Renderer::Swap()
{
	SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
}

void Renderer::drawArrays(GLsizei n)
{
	glDrawArrays(GL_TRIANGLES, 0, n);
}
