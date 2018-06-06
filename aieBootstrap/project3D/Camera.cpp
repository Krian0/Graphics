#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <Input.h>

glm::vec3 Camera::up = glm::vec3(0, 1, 0);


const float deg2Rad = 3.14159f / 180.0f;

glm::mat4 Camera::GetProjectionMatrix(float w, float h)
{
	return glm::perspective(glm::pi<float>() * 0.25f, w/h, 0.1f, 1000.f);
}

glm::mat4 Camera::GetViewMatrix()
{
	float thetaR = theta * deg2Rad;
	float phiR = phi * deg2Rad;
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	return glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
}

void Camera::Update()
{
	aie::Input* input = aie::Input::getInstance();
	float thetaR = theta * deg2Rad;
	float phiR = phi * deg2Rad;

	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));

	float deltaTime = 0.1f;

	if (input->isKeyDown(aie::INPUT_KEY_X))
		position += up * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_Z))
		position += -up * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_W))
		position += forward * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_A))
		position += -right * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_S))
		position += -forward * deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_D))
		position += right * deltaTime;

	glm::vec2 m = glm::vec2(input->getMouseX(), input->getMouseY());

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		theta += 0.05f * (m.x - lastMouse.x);
		phi -= 0.05f * (m.y - lastMouse.y);
	}

	lastMouse = m;
}