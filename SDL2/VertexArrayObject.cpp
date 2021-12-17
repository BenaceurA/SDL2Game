#include "VertexArrayObject.h"
#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
	if (glGetError() != GL_NO_ERROR)
	{
		throw std::runtime_error("failed to initialize vao!");
	}
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &id);
}

void VertexArrayObject::bind()
{
	
}

void VertexArrayObject::unbind()
{
	
}


