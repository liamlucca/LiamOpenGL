#include "shaderClass.h"

// Lee un archivo de texto y devuelve un string con todo lo que contiene el archivo de texto
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor que construye el Programa de Shader a partir de 2 shaders diferentes
Shader::Shader(const char* vertexFile, const char* fragmentFile) 
{
	// Lee vertexFile y fragmentFile y almacena los strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convierte los strings de código fuente del shader en arreglos de caracteres
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//VERTEX SHADER:
	//Creamos un valor de referencia del shader (Tipo de dato: un entero sin signo para opengl)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Le pasamos el valor de referencia, le decimos que vamos a usar 1 string para todo el shader, apuntamos al source code
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//La gpu no entiende el source code, entonces hay que compilarlo a lenguaje maquina
	glCompileShader(vertexShader);

	//FRAGMENT SHADER:
	//Creamos un valor de referencia del shader (Tipo de dato: un entero sin signo para opengl)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Le pasamos el valor de referencia, le decimos que vamos a usar 1 string para todo el shader, apuntamos al source code
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//La gpu no entiende el source code, entonces hay que compilarlo a lenguaje maquina
	glCompileShader(fragmentShader);

	//Para usar el VertexShader y FragmentShader debemos agruparlos en un shaderProgram
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Para concluir lo anterior, usamos glLinkProgram para unir todo
	glLinkProgram(ID);

	//Se puede borrar los shaders porque ya están en el pgroama
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}

// Activa el Programa del Shader
void Shader::Activate() 
{
	glUseProgram(ID);
}

// Elimina el Programa del Shader
void Shader::Delete()
{
	glDeleteProgram(ID);
}