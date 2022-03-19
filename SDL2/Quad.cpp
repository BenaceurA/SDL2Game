#include "Quad.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <array>

void Quad::bind() const
{
	bufferManager.bind();
}

void Quad::unbind() const
{
	bufferManager.unbind();
}

void Quad::addInstancedAttribute(const void* pAttribute, GLsizei byteSize) const
{
	bufferManager.addInstancedAttribute(pAttribute, byteSize);
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
	bufferManager(
		std::vector<float>{
		//POSITION		//TEXCOORD
		0.0f,	0.0f,	0.0f, 0.0f,	//bottom left
		width,	0.0f,	1.0f, 0.0f,	//bottom right
		width,	height, 1.0f, 1.0f,	//top right
		0.0f,	height, 0.0f, 1.0f,	//top left
		},
		std::vector<unsigned int>{
		0 , 1 , 2,
		2 , 3 , 0
		})
{
}

Quad::~Quad()
{
	
}

