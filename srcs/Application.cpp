#include "Application.h"
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

int windowWidth = 1920;
int windowHeight = 1080;

float DeltaTime = 0;

Application::Application(int ac, const std::vector<std::string>& av)
	: m_Argc(ac), m_Argv(av)
{
	m_WindowManager = std::make_unique<WindowManager>(*this);
	m_Object = std::make_unique<Object>(*this);
}

void Application::init()
{
	try
	{
		m_WindowManager->init();
		m_Object->init(m_Argc, m_Argv);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		glfwSetWindowShouldClose(m_WindowManager->GetWindow(), true);
	}
	std::cout << "Ca va la" << std::endl;
}

void Application::run()
{
	while (!glfwWindowShouldClose(m_WindowManager->GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear les 2 buffers pour la profondeur et la couleur
		glClearColor(1.0f, 0.5f, 0.3f, 1.0f); // couleur de fond

		update();

		std::cout << "Camera pos: " << glm::to_string(m_Camera.getPosition()) << std::endl;

		glfwPollEvents();

		glfwSwapBuffers(m_WindowManager->GetWindow());
	}
}

void Application::update()
{
	calculateDeltaTime();
	m_Camera.update(DeltaTime);
}

void Application::stop()
{
	m_WindowManager.release();
}


void calculateDeltaTime()
{
	static float lastFrame = 0.0f;
	float currentFrame = static_cast<float>(glfwGetTime());
	DeltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}