#include <iostream>
#include <glad/glad.h> //En palabras simples, GLAD administra punteros de función para OpenGL .
#include <GLFW/glfw3.h> //GLFW es una libreria que facilita el uso de opengl

//Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() 
{
	glfwInit(); //Inicializar

	//Le decimos a GLFW que version de OpenGL estamos usando, en este caso es la 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //es el numero de la izquierda "3".3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //es el numero de la derecha 3."3"
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //El perfil es algo asi como un paquete de funciones. Core (funciones modernas) y Compatibility (modernas y obsoletas)

	/*--------------VERTICES DE UN TRIANGULO EQUILATERO--------------*/

	//Tipo de dato: como un array de float normal pero para opengl (porque el tamaño de la variable se ajusta a opengl)
	//Estas son las coordenadas de los vertices de un triangulo
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	/*----------------------------------------------------*/


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

	/*-----------SHADERS-----------*/

	//VERTEX SHADER:
	//Creamos un valor de referencia del shader (Tipo de dato: un entero sin signo para opengl)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);  
	//Le pasamos el valor de referencia, le decimos que vamos a usar 1 string para todo el shader, apuntamos al source code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//La gpu no entiende el source code, entonces hay que compilarlo a lenguaje maquina
	glCompileShader(vertexShader);

	//FRAGMENT SHADER:
	//Creamos un valor de referencia del shader (Tipo de dato: un entero sin signo para opengl)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Le pasamos el valor de referencia, le decimos que vamos a usar 1 string para todo el shader, apuntamos al source code
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//La gpu no entiende el source code, entonces hay que compilarlo a lenguaje maquina
	glCompileShader(fragmentShader);

	//Para usar el VertexShader y FragmentShader debemos agruparlos en un shaderProgram
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Para concluir lo anterior, usamos glLinkProgram para unir todo
	glLinkProgram(shaderProgram);

	//Se puede borrar los shaders porque ya están en el pgroama
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*-------------- VERTEX BUFFER OBJECT (VBO)   y   VERTEX ARRAY OBJECT (VAO) ----------------*/
	
	//Enviar cosas entre el CPU y GPU es un poco lento, por lo que cuando enviamos cosas, hay que enviarlas en lotes grandes. Esos lotes son los buffers
	//Solo con los VBO tenemos un objeto con los datos bien empaquetados del vertex pero OpenGL no sabe donde encontrarlo. Para eso vamos a usar otro objeto llamado Vertex Array Object. Esto almacena punteros a uno o mas VBO y le dice a OpenGL como interpretarlos. Los VAO existen para poder cambiar rápidamente entre diferentes VBO.

	//(VertexBufferObjects) Esto por lo general es un array, pero como solo tenemos un objeto lo dejamos asi
	GLuint VAO, VBO;
	//VAO: Creamos el objeto VertexArrayObject. Debe ir antes que el VBO (MUY IMPORTANTE EL ORDEN)
	glGenVertexArrays(1, &VAO); 
	//VBO: Creamos el VertexBufferObject: glGenBuffers(le ponemos 1 de valor porque solo vamos a crear un objeto 3D, &apuntamos a la referencia)
	glGenBuffers(1, &VBO);
	//VAO: Hacemos de un determinado objeto: EL OBJETO ACTUAL. Quiere decir que cuando usemos una funcion que modificaria ese tipo de dato, vamos a modificar el OBJETO ACTUAL (binding object)... de argumento ponemos GL_ARRAY_BUFFER porque ese es el tipo de buffer que necesitamos usar para Vertex Buffer
	glBindVertexArray(VAO);
	//VBO: Hacemos de un determinado objeto: EL OBJETO ACTUAL. Quiere decir que cuando usemos una funcion que modificaria ese tipo de dato, vamos a modificar el OBJETO ACTUAL (binding object)... de argumento ponemos GL_ARRAY_BUFFER porque ese es el tipo de buffer que necesitamos usar para Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	//Ahora almacenamos nuestros vertices en el VBO... en el argumento: tipo de buffer, tamaño de los datos en bytes, los datos(vertices), uso de esta data (stream/static/dynamic___draw/read/copy)........ stream: los vertices se modificaran 1 vez y se usaran varias veces; static: los vertices se modificaran una vez y se usaran muchas muchas veces; dinamico: los vertices se modificaran varias veces y se usaran muchas muchas veces.... draw: los vertices se modificaran y se usaran para dibujar una imagen en la pantalla; 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Configuramos para que OpenGL sepa como leer VBO. Atributos: el indice atributo del vertice que queremos usar (un atributo vertex es una forma de comunicarse con un vertex shader desde el exterior), cuantos valores tenemos por vertice (en este caso 3 porque tenemos tres floats), el tipo de valores, solo importa si tenemos las coordenadas como numeros enteros (pero como no es el caso lo ponemos en false), paso de nuestros vertices que es la cantidad de datos entre cada vertice (como tenemos 3 floats, es solo de 3 veces el tamaño de un float), offset es un puntero donde commienzan los vertices en la matriz (dado que nuestros vertices comienzan justo al inicio de la matriz, le damos un puntero vacio)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Ahora habilitamos el atributo vertex para usarlo. Atributo: le ponemos el cero porque es la posicion del indice nuestro atributo Vertex
	glEnableVertexAttribArray(0);

	//OPCIONAL: es para estar seguro de que no cambiamos accidentalmente un VBO o VAO con una función. Basicamente desvinculamos VBO y VAO, vinculando a cero.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	 
	/*----------------------------------FONDO----------------------------------------*/

	//No confundir con el buffer anterior...
	//Front buffer: Es el frame buffer que se está mostrando actualmente en la pantalla.
	//Back buffer : Es la imagen que se está renderizando (todavia no se ve).

	//Le cambiamos el color a la pantalla (Los valores RGBA van del 0 al 1)
	glClearColor(0.07f, 0.08f, 0.2f,1.0f); 

	// Le especificamos que queremos usar el comando de buffer de color
	glClear(GL_COLOR_BUFFER_BIT); 

	//El color que pusimos está en el back buffer (en el front buffer tenemos el color por defecto, por lo tanto no se ve nuestro color). Con este intercambio de buffer si se va a ver el color
	glfwSwapBuffers(window);  

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
		glUseProgram(shaderProgram);
		// Vinculamos el VAO para decirle a OPENGL que queremos usarlo. (no es necesario ahcer esto porque solo tenemos un objeto y un VAO, pero es bueno acostumbrarse a esto)
		glBindVertexArray(VAO);
		// Funcion de dibujo. Especificamos tipo de primitiva que usaremos (triangulos en este caso), el indice inicial de los vertices (0 en este caso), cantidad de vertecis que queremos dibujar (en este caso 3 porque es un triangulo)
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Intercambiamos los buffers (back y front) para que la imagen se actualice en cada fotograma
		glfwSwapBuffers(window);

		/*-------------------------------------*/

		//Le decimos a glfw que procese todos los eventos de la ventana (la aparicion de la ventana, cambio de tamaño, etc...). Si no hacemos esto, la ventana estará en estado de "No responder".
		glfwPollEvents(); 
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window); //Destruimos la ventana
	glfwTerminate(); //Finalizamos GLFW
	return 0;
}