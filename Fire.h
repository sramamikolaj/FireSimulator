#ifndef FIRE_CLASS_H
#define FIRE_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"
#include<iostream>
#include<cmath>
#include<stb/stb_image.h>
#include <stdlib.h>
#include <time.h>


class Fire
{
private:
	Shader* shaderProgram;
	
	VAO VAO1;


	int circles, layers;


	int windowHeight;
	int windowWidth;

	GLfloat pointVertex[15][15][540];

	GLuint texture;
	void initTexture(const char* texPath);

	void fillArray();

public:
	Fire(int w, int h, const char* texPath);
	~Fire();

	void update();
	void activateShader();
	void render();
	Shader* getShaderProgram() { return shaderProgram; }
};



#endif