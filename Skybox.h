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

class Skybox
{
public:

	//Variables
	std::string texturesPath;
	unsigned int cubemapTexture;
	unsigned int skyboxVAO{}, skyboxVBO{}, skyboxEBO{};
	Shader* shaderProgram;
	int windowWidth, windowHeight;

	//Skybox structures
	std::vector<std::string> facesCubemap;
	float skyboxVertices[24] = {
		//   Coordinates
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f, 
		-1.0f,  1.0f, -1.0f
	};
	unsigned int skyboxIndices[36] =
	{
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};


	//Methods
	Skybox(std::string path, int windowsWidth, int windowHeight);
	~Skybox();

	//Initialization
	void initShaders();
	void initTexture();
	void initFacesCubemap();
	void initWindow(int windowWidth, int windowHeight);

	void loadCubemaps();
	void activateShader();
	void render(Camera camera);

};