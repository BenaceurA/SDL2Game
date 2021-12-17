#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
private:
	float zoom;
	void correctZoom();
public:
	Camera(glm::vec2 position, float aspect,float zoom);
	glm::vec2 position;
	float aspect;
	void setZoom(float zoom);
	float getZoom();
	glm::mat4 getView();
	glm::mat4 getProjection();
};
