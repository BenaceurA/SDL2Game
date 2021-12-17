#pragma once
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

//we never unbind this, its bound and it stays

class GLBufferManager
{
public:
	GLBufferManager(const std::vector<float>& vertices);
	~GLBufferManager();
	void bind() const;
	void unbind() const;
private:
	unsigned int _vao;
	unsigned int _vbo;
};

