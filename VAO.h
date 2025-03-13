#ifndef VAO_CLASS_
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO 
{
	public:
		// Referencia de ID para el Objeto de Arreglo de Vértices (VAO)
		GLuint ID;
		// Constructor que genera un ID de VAO
		VAO();

		// Vincula un VBO al VAO usando un cierto diseño
		void LinkVBO(VBO VBO, GLuint layout);
		// Bindea el VAO
		void Bind();
		// Desbindea el VAO
		void Unbind();
		// Elimina el VAO
		void Delete();
};

#endif