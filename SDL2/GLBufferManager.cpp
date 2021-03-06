#include "GLBufferManager.h"
#include <glad/glad.h>
#include <array>

GLBufferManager::GLBufferManager(const std::vector<float>&& vertices,const std::vector<unsigned int>&& indices)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
	glEnableVertexAttribArray(0);

	//texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float)*2));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &instanceVBO);
}

GLBufferManager::~GLBufferManager()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteBuffers(1, &instanceVBO);
	glDeleteVertexArrays(1, &_vao);
}

void GLBufferManager::bind() const
{
	glBindVertexArray(_vao);
}

void GLBufferManager::unbind() const
{
	glBindVertexArray(0);
}


void GLBufferManager::addInstancedAttribute(const void* pAttribute, GLsizei byteSize) const
{	
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, byteSize, pAttribute, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

	glVertexAttribDivisor(2, 1);
}
