#pragma once

#include "WindowManager.h"
#include <memory>
#include "Camera.h"

extern int windowHeight, windowWidth;

class Application
{
	private:
		std::unique_ptr<WindowManager> m_WindowManager;
		Camera m_Camera;
	public:
		Application();
		void init();
		void run();
		void stop();

		Camera& getCamera() { return m_Camera; }
};