#include "GLBufferManager.h"
#include <glad/glad.h>
#include <array>

GLBufferManager::GLBufferManager(const std::vector<float>& vertices)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLBufferManager::~GLBufferManager()
{
}

void GLBufferManager::bind() const
{
	glBindVertexArray(_vao);
}

void GLBufferManager::unbind() const
{
	glBindVertexArray(0);
}
