#include "Camera.h"
#include "Input.h"

Camera::Camera(glm::vec2 position,float aspect,float zoom)
	:
	position(position),
	aspect(aspect),
	zoom(zoom)
{
}

glm::mat4 Camera::getProjection()
{
	return glm::perspective(70.0f, aspect, 1.0f, 100.0f);
}



void Camera::inputCallBack()
{
	if (Input::isKeyPressed(Key::D))
		this->position.x += 0.25f;

	if (Input::isKeyPressed(Key::Q))
		this->position.x -= 0.25f;

	if (Input::isKeyPressed(Key::Z))
		this->position.y += 0.25f;

	if (Input::isKeyPressed(Key::S))
			this->position.y -= 0.25f;
}
