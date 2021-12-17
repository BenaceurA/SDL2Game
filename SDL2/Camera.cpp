#include "Camera.h"



Camera::Camera(glm::vec2 position,float aspect,float zoom)
	:
	position(position),
	aspect(aspect),
	zoom(zoom)
{
	correctZoom();
}

void Camera::setZoom(float zoom)
{
	this->zoom = zoom;
	correctZoom();
}

float Camera::getZoom()
{
	return zoom;
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(glm::vec3(position, 20.0f - zoom), glm::vec3(position, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjection()
{
	return glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);
}
void Camera::correctZoom()
{
	if (zoom < 0.0f)
		zoom = 0.0;

	if (zoom > 19.0f)
		zoom = 19.0f;
}