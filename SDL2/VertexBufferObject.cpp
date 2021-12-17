#include "VertexBufferObject.h"
#include "stdexcept"
#include <glad/glad.h>
#include <iostream>

VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)0);
	glEnableVertexAttribArray(0);

	////color
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//glEnableVertexAttribArray(1);

	if (glGetError() != GL_NO_ERROR)
	{
		throw std::runtime_error("failed to initialize vbo!");
	}
}
VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1,&id);
}


