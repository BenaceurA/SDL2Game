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
	return glm::perspective(glm::radians(80.0f), aspect, 1.0f, 100.0f);
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(glm::vec3(position, zoom), glm::vec3(position, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::inputCallBack()
{
	if (Input::isKeyPressed(Key::D))
		this->position.x += speed;

	if (Input::isKeyPressed(Key::Q))
		this->position.x -= speed;

	if (Input::isKeyPressed(Key::Z))
		this->position.y += speed;

	if (Input::isKeyPressed(Key::S))
		this->position.y -= speed;
}
