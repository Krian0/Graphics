#pragma once
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class Camera
{
public:

	Camera() : theta(0), phi(-20), position(-10, 4, 0) {}

	glm::mat4 GetProjectionMatrix(float w, float h);
	glm::mat4 GetViewMatrix();

	void Update();
	static glm::vec3 up;

private:

	float theta;
	float phi;
	glm::vec3 position;

	glm::vec2 lastMouse;
};

