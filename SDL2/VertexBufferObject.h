#pragma once
#include "Vertex.h"
#include "vector"

class VertexBufferObject
{
public:
	VertexBufferObject();
	~VertexBufferObject();
private:
	float vertices[18] = {
		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		1.0f,1.0f,
		0.0f,1.0f,
		0.0f,0.0f,
	};
	unsigned int id;
};