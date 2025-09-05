#pragma once

#include "WindowManager.h"
#include "Camera.h"
#include "Object.h"

#include <memory>
#include <vector>
#include <string>

extern int windowHeight, windowWidth;
extern float DeltaTime;

class Application
{
	private:
		int m_Argc;
		std::vector<std::string> m_Argv;
		std::unique_ptr<WindowManager> m_WindowManager;
		std::unique_ptr<Object> m_Object;
		Camera m_Camera;
	public:
		Application(int ac, const std::vector<std::string>& av);
		void init();
		void run();
		void stop();

		void update();

		Camera& getCamera() { return m_Camera; }
};