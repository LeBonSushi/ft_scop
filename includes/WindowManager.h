#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application;

class WindowManager
{
	public:
		Application& application;
	public:
		WindowManager(Application& app);
		~WindowManager();

		void init();

		inline GLFWwindow* GetWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window;
};

void frame_buffer_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void calculateDeltaTime();
