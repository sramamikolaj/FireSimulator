#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"
#include"fire.h"


int main()
{
	//GL stuff
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Okno stuff
	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL_2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //włączanie okna
	gladLoadGL();
	glViewport(0, 0, 800, 800); //mówienie gladowi o obszarze roboczym

	
	Fire testFire(800, 800);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //przygotowanie komendy 
		glClear(GL_COLOR_BUFFER_BIT); //wykonanie komendy
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		testFire.update();

		glfwSwapBuffers(window);
		glfwPollEvents(); //włączenie przetwarzania stanów okna
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}