#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader 
{
	public:
		// ID de referencia del Programa de Shader
		GLuint ID;
		// Constructor que construye el Programa de Shader a partir de 2 shaders diferentes
		Shader(const char* vertexFile, const char* fragmentFile);

		// Activa el Programa de Shader
		void Activate();
		// Elimina el Programa de Shader
		void Delete();
};

#endif
