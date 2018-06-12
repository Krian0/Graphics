#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};


	Camera		m_cam;
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::ShaderProgram	m_phongShader;


	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;
	Light				m_light;


	int					m_index;

	//Mesh				m_quadMesh;
	//glm::mat4			m_quadTransform;
};