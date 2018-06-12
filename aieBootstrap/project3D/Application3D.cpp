#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	m_index = 0;


	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	if (m_spearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_spearTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	//m_quadMesh.initializeQuad();
	//m_quadTransform = { 10, 0, 0, 0,
	//					0, 10, 0, 0,
	//					0, 0, 10, 0,
	//					0, 0, 0,  1 };


	m_light.diffuse  = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 };
	m_cam.ambientLight = { 0.25f, 0.25f, 0.25f };

	return true;
}

void Application3D::shutdown() {

	Gizmos::destroy();
}

void Application3D::update(float deltaTime) {

	// query time since application started
	float time = getTime();
	

	m_light.direction = glm::normalize(vec3(glm::cos(time * 2), glm::sin(time * 2), 0));


	m_cam.Update();

	// rotate camera
	m_projectionMatrix = m_cam.GetProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = m_cam.GetViewMatrix();

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
		if (m_index > 0)
			m_index--;

	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
		if (m_index < 1)
			m_index++;
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	m_projectionMatrix = m_cam.GetProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = m_cam.GetViewMatrix();

	m_phongShader.bind();
	m_phongShader.bindUniform("cameraPosition", m_cam.GetPosition());
	m_phongShader.bindUniform("Ia", m_cam.ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	//if (m_index == 0)
	//{
	//	auto pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform;
	//	m_phongShader.bindUniform("ProjectionViewModel", pvm);
	//	
	//	//m_phongShader.bindUniform("diffuseTexture", 0);
	//	//m_gridTexture.bind(0);
	//	m_phongShader.bindUniform("Ka", vec3(0.2f,0.2f,0.2f));
	//	m_phongShader.bindUniform("Kd", vec3(1.0f, 0.0f, 0.0f));
	//	m_phongShader.bindUniform("Ks", vec3(1.0f, 1.0f, 1.0f));
	//	m_phongShader.bindUniform("SpecularPower", 32.0f);
	//	m_phongShader.bindUniform("ModelMatrix", m_quadTransform);

	//	m_quadMesh.draw();
	//}

	if (m_index == 0)
	{
		auto pvm = m_projectionMatrix * m_viewMatrix * m_spearTransform;
		m_phongShader.bindUniform("ProjectionViewModel", pvm);

		m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));

		m_spearMesh.draw();
	}

	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw 2D gizmos using an orthogonal projection matrix (or screen dimensions)
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}