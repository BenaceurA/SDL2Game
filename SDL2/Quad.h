#pragma once
#include "GLBufferManager.h"
#include <glm/glm.hpp>
class Quad
{
	friend class Renderer;
public:
	void bind() const;
	void unbind() const;
	//there are problems with this design
	void addInstancedAttribute(const void* pAttribute, GLsizei byteSize) const;
	float getWidth();
	float getHeight();
private:
	Quad(float width, float height);
	Quad(const Quad& quad) = delete;
	Quad& operator=(const Quad& quad) = delete;
	~Quad();
	float width;
	float height;
	GLBufferManager bufferManager;

};
