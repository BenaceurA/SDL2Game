#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Inputtable.h"

class Camera : Inputtable
{
public:
	Camera(glm::vec2 position, float aspect, float zoom);
	glm::vec2 position;
	glm::mat4 getProjection();
private:
	float width;
	float height;
	float aspect;
	float zoom;
	virtual void inputCallBack() override;
};
