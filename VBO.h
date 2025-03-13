//Vertex Buffer Object (VBO)

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
	public:
		// ID de referencia del Objeto de Búfer de Vértices
		GLuint ID;
		// Constructor que genera un Objeto de Búfer de Vértices y lo vincula a los vértices
		VBO(GLfloat* vertices, GLsizeiptr size);

		// Bindea el VBO
		void Bind();
		// Desbindea el VBO
		void Unbind();
		// Elimina el VBO
		void Delete();
};

#endif