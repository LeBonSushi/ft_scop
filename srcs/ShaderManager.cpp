#include "ShaderManager.h"
#include <iostream>
#include <fstream>

// Implémentation du Singleton
ShaderManager& ShaderManager::GetInstance()
{
    static ShaderManager instance; // Instance unique créée une seule fois
    return instance;
}

// Constructeur privé
ShaderManager::ShaderManager() : m_ShaderProgram(0)
{
    std::cout << "ShaderManager instance créée" << std::endl;
}

// Destructeur privé
ShaderManager::~ShaderManager()
{
    // Nettoyage des shaders OpenGL
    for (auto& shader : m_Shaders)
    {
        glDeleteShader(shader.second);
    }
    if (m_ShaderProgram != 0)
    {
        glDeleteProgram(m_ShaderProgram);
    }
}

void CheckCompileErrors(GLuint shader, const std::string& type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

std::string ReadFile(const char* filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	if (fileStream.is_open())
	{
		std::string line;
		while (std::getline(fileStream, line))
		{
			content += line + "\n";
		}
		fileStream.close();
	}
	else
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_FOUND " << filePath << std::endl;
	}
	return content;
}

GLuint LoadShader(const char* shaderPath, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	std::string shaderCode = ReadFile(shaderPath);
	const char* shaderSource = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	CheckCompileErrors(shader, (shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT");
	
	return shader; // Ajout du return manquant
}

void ShaderManager::LoadShaders(const char* vertexPath, const char* fragmentPath)
{
	GLuint vertexShader = LoadShader(vertexPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = LoadShader(fragmentPath, GL_FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShader);
	glAttachShader(m_ShaderProgram, fragmentShader);
	glLinkProgram(m_ShaderProgram);
	CheckCompileErrors(m_ShaderProgram, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Stocker le programme dans la map avec un nom
	std::string shaderName = std::string(vertexPath) + "_" + std::string(fragmentPath);
	m_Shaders[shaderName] = m_ShaderProgram;
}

GLuint ShaderManager::GetShader(const char* name)
{
	auto it = m_Shaders.find(name);
	if (it != m_Shaders.end())
	{
		return it->second;
	}
	return m_ShaderProgram; // Retourner le programme principal si nom non trouvé
}

void ShaderManager::Use()
{
	if (m_ShaderProgram != 0)
	{
		glUseProgram(m_ShaderProgram);
	}
	else
	{
		std::cerr << "ERROR::SHADER::NO_PROGRAM_LOADED" << std::endl;
	}
}

void ShaderManager::Stop()
{
	glUseProgram(0);
}

GLuint ShaderManager::GetCurrentProgram()
{
	return m_ShaderProgram;
}