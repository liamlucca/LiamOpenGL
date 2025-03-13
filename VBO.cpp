//Vertex Buffer Object (VBO)

#include "VBO.h"

//Constructor que genera un Objeto de Búfer de Vértices y lo vincula a los vértices
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID); 														//Creamos el VertexBufferObject: glGenBuffers(le ponemos 1 de valor porque solo vamos a crear un objeto 3D, &apuntamos a la referencia)
	glBindBuffer(GL_ARRAY_BUFFER, ID);											//Hacemos de un determinado objeto : EL OBJETO ACTUAL.Quiere decir que cuando usemos una funcion que modificaria ese tipo de dato, vamos a modificar el OBJETO ACTUAL(binding object)... de argumento ponemos GL_ARRAY_BUFFER porque ese es el tipo de buffer que necesitamos usar para Vertex Buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);	//Ahora almacenamos nuestros vertices en el VBO... en el argumento : tipo de buffer, tamaño de los datos en bytes, los datos(vertices), uso de esta data(stream / static / dynamic___draw / read / copy)........stream : los vertices se modificaran 1 vez y se usaran varias veces; static : los vertices se modificaran una vez y se usaran muchas muchas veces; dinamico: los vertices se modificaran varias veces y se usaran muchas muchas veces....draw : los vertices se modificaran y se usaran para dibujar una imagen en la pantalla;
}

//Bindea el VBO
void VBO::Bind()
{
	//Hacemos de un determinado objeto: EL OBJETO ACTUAL.Quiere decir que cuando usemos una funcion que modificaria ese tipo de dato, vamos a modificar el OBJETO ACTUAL(binding object)... de argumento ponemos GL_ARRAY_BUFFER porque ese es el tipo de buffer que necesitamos usar para Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);	
}

//Desbindea el VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Borra el VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}