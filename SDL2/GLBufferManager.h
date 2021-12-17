#pragma once
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

//we never unbind this, its bound and it stays

class GLBufferManager
{
public:
	GLBufferManager();
	~GLBufferManager();

private:
	VertexArrayObject vao; //generate vao and binds it
	VertexBufferObject vbo; //generate vbo and init it with inVertices
};

