#pragma once
#include <vector>

//we never unbind this, its bound and it stays

typedef int GLsizei;

class GLBufferManager
{
public:

	GLBufferManager(const std::vector<float>&& vertices, const std::vector<unsigned int>&& indices);

	~GLBufferManager();

	void bind() const;

	void unbind() const;

	//you can only add 1 instance attribute modelPos (TEST : ADD MORE PARAMS/CHANGES FOR FLEXIBILTY CAUSE THIS ONLY ADD A VEC2 ATTRIBUTE)
	void addInstancedAttribute(const void* pAttribute, GLsizei size) const;

private:
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
	unsigned int instanceVBO;
};

