#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"



int main()
{

	glfwInit();
	//wersje i profile - profil = pakiet funkcji
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	GLfloat pointVertex[] = {
		-0.2, -0.5, 0,
		0.2, -0.5, 0,
		0, -0.5, 0
		};




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

	
	// Generates Shader object using shaders 
	Shader shaderProgram("spark.vert", "spark.frag");


	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(pointVertex, sizeof(pointVertex));
	VAO1.LinkVBO(VBO1, 0);
	
	GLfloat temp = 1;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //przygotowanie komendy 
		glClear(GL_COLOR_BUFFER_BIT); //wykonanie komendy
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		

		if (temp <= 0.1) {
			pointVertex[1] = -0.5;
			pointVertex[4] = -0.5;
			pointVertex[7] = -0.5;
			temp = 1;
			};
		

		shaderProgram.Activate(); //włącz shadery
		pointVertex[1] += 0.0002;
		pointVertex[4] += 0.0002;
		pointVertex[7] += 0.0002;

		VBO1 = VBO(pointVertex, sizeof(pointVertex));
		VAO1.LinkVBO(VBO1, 0); // Links VBO to VAO
		VAO1.Bind();



		int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
		
		
		glPointSize(50);
		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, temp);
		
		glDrawArrays(GL_POINTS, 0, 2);

		glPointSize(10);
		glUniform4f(vertexColorLocation, 1.0f, 0.5f, 0.1f, temp);
		glDrawArrays(GL_POINTS, 2, 1);
		

		glfwSwapBuffers(window);
		glfwPollEvents(); //włączenie przetwarzania stanów okna

		
		temp -= 0.0002;

		
	}


	VAO1.Delete();
	VBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}