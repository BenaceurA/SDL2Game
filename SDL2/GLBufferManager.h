#pragma once
#include <vector>

//we never unbind this, its bound and it stays

class GLBufferManager
{
public:
	GLBufferManager(const std::vector<float>&& vertices, const std::vector<unsigned int>&& indices);
	~GLBufferManager();
	void bind() const;
	void unbind() const;
private:
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
};

