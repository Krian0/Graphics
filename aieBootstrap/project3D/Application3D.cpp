#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() 
{

}

Application3D::~Application3D() 
{

}

bool Application3D::startup() 
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);


	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");


	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}


	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalmap.frag");


	if (m_normalMapShader.link() == false)
	{
		printf("Shader Error: %s\n", m_normalMapShader.getLastError());
		return false;
	}

	if (m_spearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_spearTransform = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_bunnyMesh.load("./stanford/Bunny.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_bunnyTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0,    1
	};

	if (m_dragonMesh.load("./stanford/Dragon.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_dragonTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0,    1
	};

	if (m_buddhaMesh.load("./stanford/Buddha.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_buddhaTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0,    1
	};

	if (m_lucyMesh.load("./stanford/Lucy.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_lucyTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0,    1
	};

	m_light.diffuse  = { 1, 1, 1 };
	m_light.specular = { 1, 1, 1 };
	m_cam.ambientLight = { 0.80f, 0.80f, 0.80f };
	m_index = 0;

	return true;
}

void Application3D::shutdown() 
{
	Gizmos::destroy();
}

void Application3D::update(float deltaTime) 
{
	m_light.direction = glm::vec3(0.5f, 0, 1);
	m_cam.Update();

	// rotate camera
	m_projectionMatrix = m_cam.GetProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = m_cam.GetViewMatrix();

	Gizmos::clear();

	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT) && m_index > 0)
		m_index--;
	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT) && m_index < 4)
		m_index++;
}

void Application3D::draw() 
{
	clearScreen();

	m_projectionMatrix = m_cam.GetProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = m_cam.GetViewMatrix();


	if (m_index == 0) 
	{
		m_normalMapShader.bind();
		m_normalMapShader.bindUniform("cameraPosition", m_cam.GetPosition());
		m_normalMapShader.bindUniform("Ia", m_cam.ambientLight);
		m_normalMapShader.bindUniform("Id", m_light.diffuse);
		m_normalMapShader.bindUniform("Is", m_light.specular);
		m_normalMapShader.bindUniform("lightDirection", m_light.direction);

		auto pvm = m_projectionMatrix * m_viewMatrix * m_spearTransform;
		m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
		m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));
		m_spearMesh.draw();
	}
	else
	{
		m_phongShader.bind();
		m_phongShader.bindUniform("cameraPosition", m_cam.GetPosition());
		m_phongShader.bindUniform("Ia", m_cam.ambientLight);
		m_phongShader.bindUniform("Id", m_light.diffuse);
		m_phongShader.bindUniform("Is", m_light.specular);
		m_phongShader.bindUniform("lightDirection", m_light.direction);


	}

	if (m_index == 1)
	{
		auto pvm = m_projectionMatrix * m_viewMatrix * m_bunnyTransform;
		m_phongShader.bindUniform("ProjectionViewModel", pvm);
		m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);

		m_bunnyMesh.draw();
	}

	if (m_index == 2)
	{
		auto pvm = m_projectionMatrix * m_viewMatrix * m_dragonTransform;
		m_phongShader.bindUniform("ProjectionViewModel", pvm);
		m_phongShader.bindUniform("ModelMatrix", m_dragonTransform);

		m_dragonMesh.draw();
	}

	if (m_index == 3)
	{
		auto pvm = m_projectionMatrix * m_viewMatrix * m_buddhaTransform;
		m_phongShader.bindUniform("ProjectionViewModel", pvm);
		m_phongShader.bindUniform("ModelMatrix", m_buddhaTransform);
		m_buddhaMesh.draw();
	}

	if (m_index == 4)
	{
		auto pvm = m_projectionMatrix * m_viewMatrix * m_lucyTransform;
		m_phongShader.bindUniform("ProjectionViewModel", pvm);
		m_phongShader.bindUniform("ModelMatrix", m_lucyTransform);
		m_lucyMesh.draw();
	}

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}