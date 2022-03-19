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
	glm::mat4 getView();
private:
	float aspect;
	float zoom;
	float speed = 1.15f;
	virtual void inputCallBack() override;
};
