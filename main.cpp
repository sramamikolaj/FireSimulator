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
	//GL initialiation
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Window initialization
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
	//Components initialization
	Fire fire("Resources/Images/fire_particle.jpg");
	Ground ground("Resources/Images/grass.jpg");
	Camera camera(windowWidth, windowHeight, 0.005, glm::vec3(0.0f, 0.15f, 1.0f));
	Skybox skybox("Resources/Images/Night/", windowWidth, windowHeight);
	//Time variables
	static double limitFPS = 1.0 / 60.0;
	double prevTime = glfwGetTime();
	double diff = 0;
	double currTime = 0;
	//Main program loop
	while (!glfwWindowShouldClose(window)) {
		//Time calculation
		currTime = glfwGetTime();
		diff += (currTime - prevTime) / limitFPS;
		prevTime = currTime;
		//Enable blending for fire particles (point sprites)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Update fire and camera position if enough time has passed
		while (diff >= 1.0) {
			camera.Inputs(window);
			fire.update();
			diff--;
		}
		//Render components
		skybox.render(camera);
		ground.activateShader();
		camera.Matrix(45.0f, 0.1f, 100.0f, *(ground.getShaderProgram()), "camMatrix");
		ground.render();
		fire.activateShader();
		camera.Matrix(45.0f, 0.1f, 100.0f, *(fire.getShaderProgram()), "camMatrix");
		fire.render();
		//Buffer swap and pool events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}