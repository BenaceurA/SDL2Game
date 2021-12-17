#pragma once
#include "Vertex.h"
#include "vector"
#include "VertexBufferObject.h"

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();
	void bind();
	void unbind();
private:
	unsigned int id;
};

