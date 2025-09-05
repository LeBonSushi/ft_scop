#include "Camera.h"
#include "Application.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : m_Position(0, 0, -3),
					m_Yaw(90.0f),
					m_Pitch(0.0f),
					m_Up(0, 1, 0),
					m_Front(0, 0, 1),
					m_Right(1, 0, 0),
					m_ViewMatrice(glm::lookAt(m_Position, m_Position + m_Front, m_Up)),
					m_ProjMatrice(glm::infinitePerspective(static_cast<float>(glm::radians(FOV)), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f))
{
}

void Camera::handleMouseMovement(float xpos, float ypos, float DeltaTime)
{
	static bool firstMouse = true;
	static float lastX = static_cast<float>(windowWidth) / 2.0f;
	static float lastY = static_cast<float>(windowHeight) / 2.0f;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	xoffset *= MOUSE_SENSITIVITY * DeltaTime;
	yoffset *= MOUSE_SENSITIVITY * DeltaTime;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up    = glm::normalize(glm::cross(m_Right, m_Front));

	m_ViewMatrice = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::handleInput(float DeltaTime)
{
	const float cameraSpeed = CAMERA_SPEED * DeltaTime;

	GLFWwindow* window = glfwGetCurrentContext();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position += cameraSpeed * m_Front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position -= cameraSpeed * m_Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position -= m_Right * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position += m_Right * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_Position += m_Up * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_Position -= m_Up * cameraSpeed;
}

void Camera::update(float DeltaTime)
{
	handleInput(DeltaTime);
	updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	m_ViewMatrice = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}