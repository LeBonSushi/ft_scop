#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>

class ShaderManager
{
	public:
		// Méthode pour obtenir l'instance unique
		static ShaderManager& GetInstance();
		
		// Méthodes publiques
		void LoadShaders(const char* vertexPath, const char* fragmentPath);
		GLuint GetShader(const char* name);
		void Use(); // Active le programme shader pour le rendu
		GLuint GetCurrentProgram(); // Retourne l'ID du programme actuel
		void Stop(); // Libère les ressources
		
		// Supprimer les constructeurs de copie et d'assignation
		ShaderManager(const ShaderManager&) = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;
		
	private:
		// Constructeur privé
		ShaderManager();
		~ShaderManager();
		
		// Membres privés
		std::unordered_map<std::string, GLuint> m_Shaders;
		GLuint m_ShaderProgram;
};