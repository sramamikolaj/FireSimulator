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

	Camera camera(800, 800, glm::vec3(0.0f, 0.0f, 2.0f));


	///PODŁOGA STUFF

	VAO VAO1;
	VAO1.Bind();
	GLfloat vertices[] =
	{
		20.0f, 0, -10.0f, // Lower left corner
		-20.0f, 0, -10.0f, // Lower right corner
		10.5f, 0, 10.0f // Upper corner
	};
	VBO VBO1(vertices, sizeof(vertices));
	VAO1.LinkVBO(VBO1, 0);
	Shader shaderPr("default.vert", "default.frag");

	///////////////

	while (!glfwWindowShouldClose(window)) {


		glClearColor(0.05, 0.08, 0.21, 1.0f); //przygotowanie komendy 
		glClear(GL_COLOR_BUFFER_BIT); //wykonanie komendy
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



		camera.Inputs(window);
		
		

		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		
		///PODŁOGA STUFF
		shaderPr.Activate();
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderPr, "camMatrix");
		VAO1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		///////////////


		testFire.update();
		camera.Matrix(45.0f, 0.1f, 100.0f, *(testFire.getShaderProgram()), "camMatrix");
		testFire.render();

		
		

		glfwSwapBuffers(window);
		glfwPollEvents(); //włączenie przetwarzania stanów okna
	}

	VBO1.Delete();
	VAO1.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}