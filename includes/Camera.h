#pragma once

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define FOV 45.0
#define MOUSE_SENSITIVITY 1.0

class Camera
{
	public:
		Camera();
		~Camera() = default;

		glm::vec3 getPosition() const { return m_Position; }
		void setPosition(const glm::vec3& newPosition) { m_Position = newPosition; }
		void handleMouseMovement(float xpos, float ypos);

	private:
		glm::vec3 m_Position;
		float m_Yaw;
		float m_Pitch;

		glm::vec3 m_Up;
		glm::vec3 m_Front;
		glm::vec3 m_Right;
		glm::mat4 m_ViewMatrice;
		glm::mat4 m_ProjMatrice;
};