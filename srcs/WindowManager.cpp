#include "WindowManager.h"
#include "Application.h"

WindowManager::WindowManager(Application& app) : application(app) {}

WindowManager::~WindowManager()
{
	glfwTerminate();
}

void WindowManager::init()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

	m_Window = glfwCreateWindow(windowWidth, windowHeight, "ft_scop", nullptr, nullptr);

	if (!m_Window)
		throw std::runtime_error("Couldn't initialize Window.");

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Couldn't initialize glad.");

	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(m_Window, frame_buffer_callback);
	glfwSetKeyCallback(m_Window, key_callback);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); // un peu plus permissif que LESS

	glfwSetWindowUserPointer(m_Window, &application);

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void frame_buffer_callback(GLFWwindow* window, int width, int height)
{
	(void) window;
	windowHeight = height;
	windowWidth = width;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (app)
	{
		app->getCamera().handleMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos), DeltaTime);
	}
}