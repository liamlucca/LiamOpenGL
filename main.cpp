#include <iostream>
#include <glad/glad.h> //En palabras simples, GLAD administra punteros de función para OpenGL .
#include <GLFW/glfw3.h> //GLFW es una libreria que facilita el uso de opengl

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

	//Front buffer: Es el frame buffer que se está mostrando actualmente en la pantalla.
	//Back buffer : Es la imagen que se está renderizando (todavia no se ve).

	//Le cambiamos el color a la pantalla (Los valores RGBA van del 0 al 1)
	glClearColor(0.07f, 0.08f, 0.2f,1.0f); 

	// Le especificamos que queremos usar el comando de buffer de color
	glClear(GL_COLOR_BUFFER_BIT); 

	//El color que pusimos está en el back buffer (en el front buffer tenemos el color por defecto, por lo tanto no se ve nuestro color). Con este intercambio de buffer si se va a ver el color
	glfwSwapBuffers(window);  

	//Hacemos el bucle while para que el programa no termine apenas lo ejecutemos (termina cuando apretemos el boton de cerrar)
	while (!glfwWindowShouldClose(window))
	{
		//Le decimos a glfw que procese todos los eventos de la ventana (la aparicion de la ventana, cambio de tamaño, etc...). Si no hacemos esto, la ventana estará en estado de "No responder".
		glfwPollEvents(); 
	}

	glfwDestroyWindow(window); //Destruimos la ventana
	glfwTerminate(); //Finalizamos GLFW
	return 0;
}