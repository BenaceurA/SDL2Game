#include "Quad.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>

void Quad::bind() const
{
	bufferManager.bind();
}

void Quad::unbind() const
{
	bufferManager.unbind();
}

float Quad::getWidth()
{
	return width;
}

float Quad::getHeight()
{
	return height;
}

Quad::Quad(float width, float height)
	:
	width(width),
	height(height),
	bufferManager(std::vector<float>{
		0.0f,	0.0f,	//bottom left
		width,	0.0f,	//bottom right
		width,	height,	//top right
		width,	height,	//top right
		0.0f,	height,	//top left
		0.0f,	0.0f	//bottom left
		})
{
}

Quad::~Quad()
{
	
}

