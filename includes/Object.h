#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>

#define DEFAULT_OBJ_PATH "./resources/cube.obj"

class Application;

class Object
{
	private:
		std::string m_ObjPath;
		Application& m_Application;

		//make vectors for normal and texture coords as well
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<float> m_Normals;
		std::vector<float> m_TexCoords;


		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
	public:
		Object(Application& app);
		~Object();
		void init(int ac, const std::vector<std::string>& av);
};