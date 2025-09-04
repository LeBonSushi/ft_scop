#include "Application.h"
#include <iostream>

int windowWidth = 1920;
int windowHeight = 1080;

Application::Application()
{
	m_WindowManager = std::make_unique<WindowManager>(*this);
}

void Application::init()
{
	try
	{
		m_WindowManager->init();
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
		std::cout << "Window height: " << windowHeight << ", window width: " << windowWidth << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear les 2 buffers pour la profondeur et la couleur
		glClearColor(1.0f, 0.5f, 0.3f, 1.0f); // couleur de fond

		glfwPollEvents();

		glfwSwapBuffers(m_WindowManager->GetWindow());
	}
}

void Application::stop()
{
	m_WindowManager.release();
}