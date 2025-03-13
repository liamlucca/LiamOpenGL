#include <iostream>
#include <glad/glad.h> //En palabras simples, GLAD administra punteros de función para OpenGL .
#include <GLFW/glfw3.h> //GLFW es una libreria que facilita el uso de opengl

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


//--------------VERTICES DE UN TRIANGULO EQUILATERO--------------

//Tipo de dato: como un array de float normal pero para opengl (porque el tamaño de la variable se ajusta a opengl)
//Estas son las coordenadas de los vertices de 3 triangulos unidos
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			// Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		// Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		// Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		// Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f			// Inner down
};

/*----------------------------------------------------*/

GLuint indices[] =
{
	0, 3, 5,		//Triangulo de abajo a la izquierda
	3, 2, 4,		//Triangulo de abajo a la derecha
	5, 4, 1			//Triangulo de arriba
};




int main()
{
	glfwInit(); //Inicializar

	//Le decimos a GLFW que version de OpenGL estamos usando, en este caso es la 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //es el numero de la izquierda "3".3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //es el numero de la derecha 3."3"
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //El perfil es algo asi como un paquete de funciones. Core (funciones modernas) y Compatibility (modernas y obsoletas)

	//Creamos la ventana
	GLFWwindow* window = glfwCreateWindow(800, 800, "Liam OpenGL", NULL, NULL); //width, height, title, fullscreen, ?

	//En caso de que la ventana no se cree, damos un error
	if (window == NULL) 
	{
		std::cout << "Failed to create GLDW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Hay que decirle que vamos a USAR LA VENTANA que creamos... Hace que la ventana forme parte del contexto actual. El contexto es una especie de objeto que contiene todo lo de OpenGL.
	glfwMakeContextCurrent(window); 
	
	//Le decimos a glad que cargue las configuraciones para opengl
	gladLoadGL(); 

	//Le indicamos el area de la ventana  donde se va a renderizar opengl... va desde abajo a la izquierda (0,0), hasta arriba a la derecha (800,800)
	glViewport(0, 0, 800, 800);

	// Genera un objeto Shader usando los shaders default.vert y default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Genera un Objeto de Arreglo de Vértices y lo enlaza
	VAO VAO1;
	VAO1.Bind();

	// Genera un Objeto de Búfer de Vértices y lo vincula a los vértices  
	VBO VBO1(vertices, sizeof(vertices));
	// Genera un Objeto de Búfer de Elementos y lo vincula a los índices  
	EBO EBO1(indices, sizeof(indices));

	// Vincula el VBO al VAO  
	VAO1.LinkVBO(VBO1, 0);
	// Desenlaza todo para evitar modificarlo accidentalmente
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	/*----------------------------------------------------------------------------*/

	//Hacemos el bucle while para que el programa no termine apenas lo ejecutemos (termina cuando apretemos el boton de cerrar)
	while (!glfwWindowShouldClose(window))
	{
		/*-------------Triangulo----------------*/

		//Le cambiamos el color a la pantalla (Los valores RGBA van del 0 al 1)
		glClearColor(0.07f, 0.08f, 0.2f, 1.0f);
		// Le especificamos que queremos usar el comando de buffer de color
		glClear(GL_COLOR_BUFFER_BIT);
		// Activamos el programa shader que creamos
		shaderProgram.Activate();
		// Vinculamos el VAO para decirle a OPENGL que queremos usarlo. (no es necesario ahcer esto porque solo tenemos un objeto y un VAO, pero es bueno acostumbrarse a esto)
		VAO1.Bind();
		// Funcion de dibujo. Especificamos tipo de primitiva que usaremos (triangulos en este caso), cuantos indices queremos usar (9 porque son 3 triangulos), el tipo de dato de los indices, el indice de los indices (en este caso es 0)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Intercambiamos los buffers (back y front) para que la imagen se actualice en cada fotograma
		glfwSwapBuffers(window);

		/*-------------------------------------*/

		//Le decimos a glfw que procese todos los eventos de la ventana (la aparicion de la ventana, cambio de tamaño, etc...). Si no hacemos esto, la ventana estará en estado de "No responder".
		glfwPollEvents(); 
	}

	//Destruimos todo los objetos que hemos creados
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//Destruimos la ventana
	glfwDestroyWindow(window); 
	//Finalizamos GLFW
	glfwTerminate();
	return 0;
}