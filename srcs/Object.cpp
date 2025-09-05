#include "Object.h"

#include <iostream>

Object::Object(Application& app) : m_Application(app)
{
}

Object::~Object()
{
}

void Object::init(int ac, const std::vector<std::string>& av)
{
	if (ac < 2)
	{
		std::cout << "No .obj file provided." << std::endl;
		std::cout << "Trying to load default file: " << DEFAULT_OBJ_PATH << std::endl;
		m_ObjPath = DEFAULT_OBJ_PATH;
	}
	else if (ac == 2)
	{
		m_ObjPath = av[1];
	}
	else
	{
		throw std::runtime_error("Too many arguments.");
	}
	std::cout << "Loading .obj file: " << m_ObjPath << std::endl;

	loadObj();
}