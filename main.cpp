#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"
#include"fire.h"
#include"camera.h"
#include"ground.h"


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

	Fire testFire(800, 800, 50);
	Ground ground(800, 800);
	Camera camera(800, 800, glm::vec3(0.0f, 0.15f, 2.0f));

	while (!glfwWindowShouldClose(window)) {


		glClearColor(0.05, 0.08, 0.21, 1.0f); //przygotowanie komendy 
		glClear(GL_COLOR_BUFFER_BIT); //wykonanie komendy
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		camera.Inputs(window);
	
		ground.activateShader();
		camera.Matrix(45.0f, 0.1f, 100.0f, *(ground.getShaderProgram()), "camMatrix");
		ground.render();

		testFire.update();
		testFire.activateShader();
		camera.Matrix(45.0f, 0.1f, 100.0f, *(testFire.getShaderProgram()), "camMatrix");
		testFire.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}