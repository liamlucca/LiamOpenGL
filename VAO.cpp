#include "VAO.h"

// Constructor que genera una ID VAO
VAO::VAO() 
{
	glGenVertexArrays(1, &ID);
}

// Vincula un VBO al VAO usando un cierto diseño
void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	//Configuramos para que OpenGL sepa como leer VBO. Atributos: el indice atributo del vertice que queremos usar (un atributo vertex es una forma de comunicarse con un vertex shader desde el exterior), cuantos valores tenemos por vertice (en este caso 3 porque tenemos tres floats), el tipo de valores, solo importa si tenemos las coordenadas como numeros enteros (pero como no es el caso lo ponemos en false), paso de nuestros vertices que es la cantidad de datos entre cada vertice (como tenemos 3 floats, es solo de 3 veces el tamaño de un float), offset es un puntero donde comienzan los vertices en la matriz (dado que nuestros vertices comienzan justo al inicio de la matriz, le damos un puntero vacio)
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//Ahora habilitamos el atributo vertex para usarlo. Atributo: le ponemos el cero porque es la posicion del indice nuestro atributo Vertex
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

//Bindea el VAO
void VAO::Bind() 
{
	//Hacemos de un determinado objeto: EL OBJETO ACTUAL. Quiere decir que cuando usemos una funcion que modificaria ese tipo de dato, vamos a modificar el OBJETO ACTUAL (binding object)... de argumento ponemos GL_ARRAY_BUFFER porque ese es el tipo de buffer que necesitamos usar para Vertex Buffer
	glBindVertexArray(ID);
}

//Desbindeamos
void VAO::Unbind()
{
	glBindVertexArray(0);
}

//Borramos el VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}