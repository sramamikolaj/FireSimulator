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
#include <vector>
#include"Skybox.h"


int main()
{
	//GL stuff
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Okno stuff
	int windowWidth = 800;
	int windowHeight = 800;
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OPENGL_2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);


	Fire fire(windowWidth, windowHeight, "Resources/Images/fire_particle.jpg");
	Ground ground(windowWidth, windowHeight, "Resources/Images/grass.jpg");
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.15f, 1.0f));
	Skybox skybox("Resources/Images/Night/", windowWidth, windowHeight);

	static double limitFPS = 1.0 / 60.0;
	double prevTime = glfwGetTime();
	double diff = 0;
	double currTime = 0;
	
	
	//Create and acrivate skybox shader and textures
	Shader skyboxShader("Resources/Shaders/skybox.vert", "Resources/Shaders/skybox.frag");

	skybox.initTexture();
	skybox.loadCubemaps();


	while (!glfwWindowShouldClose(window)) {
		currTime = glfwGetTime();
		diff += (currTime - prevTime) / limitFPS;
		prevTime = currTime;

		glClearColor(0.05, 0.08, 0.21, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		while (diff >= 1.0) {
			camera.Inputs(window);
			fire.update();

			diff--;
		}

		camera.resetPosition();

		skybox.render(skyboxShader, camera);
		ground.activateShader();
		camera.Matrix(45.0f, 0.1f, 100.0f, *(ground.getShaderProgram()), "camMatrix");
		ground.render();
		fire.activateShader();
		camera.Matrix(45.0f, 0.1f, 100.0f, *(fire.getShaderProgram()), "camMatrix");
		fire.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}