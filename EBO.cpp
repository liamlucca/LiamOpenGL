#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {
	glGenBuffers(1, &ID); 												
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);											
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	//Hacemos de un determinado objeto: EL OBJETO ACTUAL.Quiere decir que cuando usemos una funcion que modificaria ese tipo de dato, vamos a modificar el OBJETO ACTUAL(binding object)... de argumento ponemos GL_ARRAY_BUFFER porque ese es el tipo de buffer que necesitamos usar para Vertex Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	//Desbindeamos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}